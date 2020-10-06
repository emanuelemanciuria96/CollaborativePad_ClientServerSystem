//
// Created by Windows on 25/03/2020.
//

#include <QtGui/QPainter>
#include <QtWidgets/QFileDialog>
#include <QtPrintSupport/QPrinter>
#include "EditorGUI.h"
#include <QScrollBar>
#include <QtWidgets/QStyle>
#include <QtWidgets/QToolTip>
#include <tuple>

EditorGUI::EditorGUI(SharedEditor *model, bool highlight, QWidget *parent) : QWidget(parent){
    remoteCursors = std::make_shared<std::list<RemoteCursor>>();
    signalBlocker = false;
    myCursorPosUpdateBlocker = false;
    highlightEditor = highlight;
    setModel(model);
    setUpGUI();
    setWindowTitle(QCoreApplication::applicationName());
    posLastChar = -1;
    timer = new QTimer(this);
    curBlockerTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EditorGUI::enableSendCursorPos);
    connect(timer, &QTimer::timeout, this, &EditorGUI::flushInsertQueue);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this,&EditorGUI::handleCursorPosChanged);
    connect(textEdit, &MyTextEdit::tipRequest, this,&EditorGUI::highlightedTip);
    connect(textEdit, &QTextEdit::currentCharFormatChanged, this, &EditorGUI::checkCharFormat);

    timer->start(200); //tra 150 e 200 dovrebbe essere ottimale
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
    textEdit = new MyTextEdit(remoteCursors, this);
    setLayout(new QVBoxLayout(this));
    this->layout()->setContentsMargins(30, 0, 30, 0);
    this->layout()->addWidget(textEdit);
    this->layout()->setAlignment(Qt::AlignCenter);

    textEdit->document()->setDocumentMargin(65);
    textEdit->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    textEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    textEdit->setLineWrapMode(QTextEdit::FixedPixelWidth);
    textEdit->setLineWrapColumnOrWidth(880);
    textEdit->setMaximumWidth(888);
//    textEdit->setAlignment(Qt::AlignCenter);

    connect(this, SIGNAL(clear()), textEdit, SLOT(clear()));

    textEdit->setStyleSheet("QTextEdit{border-style:none}"
                    "QScrollBar:vertical {background:white; width:8px; margin: 0px 0px 0px 0px;}"
                    "QScrollBar::handle:vertical {background: #ECECEC; border:0px solid lightgray; border-radius:4px;}"
//                  "QScrollBar::add-line:vertical{height:0px; subcontrol-position: bottom; subcontrol-origin: margin;"
//                  "QScrollBar::sub-line:vertical {height: 0px width:0px; subcontrol-position: top; subcontrol-origin: margin; "
                    "QScrollBar:horizontal {background:white; height:8px; margin: 0px 0px 0px 0px;}"
                    "QScrollBar::handle:horizontal {background: #ECECEC; border:0px solid lightgray; border-radius: 4px}"
                  );

    textEdit->setFocus();
    setCurrentFileName(QString());

    connect(textEdit->document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(contentsChange(int, int, int)));
    connect(textEdit, &QTextEdit::copyAvailable, this, &EditorGUI::setSelected);

//    load("./file.txt");
//    loadHighlights();
}

//slot per l'editor con highlight
void EditorGUI::loadHighlights() {
//    if(highlightEditor) {
        auto i = 0;
        for (auto s : model->getSiteIds()) {
            highlight(i, s);
            i++;
        }
//    }
}

void EditorGUI::setCurrentFileName(QString filename) {
    this->fileName = filename;
}

void EditorGUI::setModel(SharedEditor* _model) {
    this->model = _model;
}

//chiamata quando si effettuano modifiche sul editor
void EditorGUI::contentsChange(int pos, int charsRemoved, int charsAdded) {
    int i = 0;
    if (!signalBlocker) {
        myCursorPosUpdateBlocker = true;
        curBlockerTimer->start(500);
//        auto blocks = textEdit->document()->blockCount();
//        auto pages = textEdit->document()->pageCount();
//        std::cout << "Numero blocchi: " << blocks << " Numero pagine: " << pages << std::endl;

        //std::cout << "invio caratteri" << std::endl;
        if (charsRemoved > 0) {  //sono stati cancellati dei caratteri
            //std::cout << "Cancellazione carattere " << index << std::endl;
            model->localErase(pos,charsRemoved);
            QString str = "";
            for (i = 0; i < charsRemoved; i++) {
                str+="x";
            }
            emit updateOther(pos+1, str,model->getSiteId(), Message::removal);
        }
        if (charsAdded > 0) {  //sono stati aggiunti caratteri
            //std::cout << "Inserimento carattere " << index << std::endl;
            QString str = "";
            for (i = 0; i < charsAdded; i++) {
                str+=textEdit->document()->characterAt(pos + i);
            }
            model->localInsert(pos, str, textEdit->currentCharFormat());
            emit updateOther(pos+1, str,model->getSiteId(), Message::insertion);
        }
//        updateRemoteCursors(model->getSiteId(),pos);
    }
}

void EditorGUI::insertText(qint32 pos, const QString &value, qint32 siteId) {
    pos--;
    RemoteCursor *cursor;

    cursor = getRemoteCursor(siteId);
//    std::cout << "Inseriti da siteId: " << siteId << std::endl;
    ///blocco l'invio della posizione del mio cursore quando ricevo modifiche
    myCursorPosUpdateBlocker = true;
    curBlockerTimer->start(500);

    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    if(highlightEditor)
        cursor->setCharFormat(getHighlightFormat(siteId));

    cursor->insertText(value);
    //std::cout << "Inseriti " << value.size() << " caratteri in " << index << std::endl;
    signalBlocker = !signalBlocker;
    if(siteId!= model->getSiteId())
        drawLabel(cursor);
//    updateRemoteCursors(siteId,index, Message::insertion);
}

bool EditorGUI::checkSiteId(RemoteCursor &rc, qint32 siteId) {
    return rc.getSiteId() == siteId;
}

void EditorGUI::deleteText(qint32 pos, qint32 siteId, qint32 n) {
    pos--;
    RemoteCursor *cursor;

    cursor = getRemoteCursor(siteId);
    ///blocco l'invio della posizione del mio cursore quando ricevo modifiche
    myCursorPosUpdateBlocker = true;
    curBlockerTimer->start(500);

    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    cursor->setPosition(pos + n, QTextCursor::KeepAnchor);
    signalBlocker = !signalBlocker;
    cursor->removeSelectedText();
    //std::cout << "Rimosso " << index << std::endl;
    signalBlocker = !signalBlocker;
    if(siteId!= model->getSiteId())
        drawLabel(cursor);
//    updateRemoteCursors(siteId,index, Message::removal);
}

//chiamata quando si ricevono modifiche
void EditorGUI::updateSymbols(qint32 pos, QString s, qint32 siteId, Message::action_t action) {
//    std::cout<<"updateSymbols inizio" << std::endl;
    if (action == Message::removal) {
//        flushInsertQueue();     //prima della delete inserisco eventuali caratteri in coda
        deleteText(pos, siteId, s.size());
    } else {
        insertText(pos, s, siteId);
//        if(posLastChar<0 || index!=posLastChar+1) {
//            flushInsertQueue();
//            posQueue = index;
//            siteIdQueue = siteId;
//        }
//        insertQueue.push(value);
//        posLastChar = index;
    }
//    std::cout<<"updateSymbols fine" << std::endl;

}

void EditorGUI::updateRemoteCursors(qint32 mySiteId, int pos) {
    // aggiorno la posizione degli altri cursori

    for (auto & remoteCursor : *remoteCursors) {
        if (remoteCursor.getSiteId() != mySiteId && remoteCursor.getSiteId()>0) {
            if(!remoteCursor.labelName->isHidden())
                drawLabel(&remoteCursor);
//            auto newPosition = it->position();
//            if (newPosition > index) {
//                if (action == Message::insertion)
//                    it->setPosition(newPosition + 1, QTextCursor::MoveAnchor);
//                else
//                    it->setPosition(newPosition - 1, QTextCursor::MoveAnchor);
//            }
        }
    }
}


RemoteCursor *EditorGUI::getRemoteCursor(qint32 siteId) {
    RemoteCursor *cursor;
    /// da gestire con una eccezione
    if(siteId < 0)
        return nullptr;
//    std::cout << "Lista siteId dei cursori remoti:" << std::endl;
    auto it = std::find_if(remoteCursors->begin(), remoteCursors->end(), [siteId](const RemoteCursor &c) {
//        std::cout << "SiteId: " << c.getSiteId() << std::endl;
        return (c.getSiteId() == siteId);
    });
    if (it == remoteCursors->end()) {
        auto username = QString();
        username = (siteId>0 && siteId != model->getSiteId()) ? file_writers.at(siteId) : "me";
        remoteCursors->emplace_back(textEdit->document(), siteId, username);
        cursor = &remoteCursors->back();
        if(siteId!=0 && siteId!=model->getSiteId())
            connect(cursor->labelTimer, &QTimer::timeout, cursor->labelName, &QLabel::hide);
    } else
        cursor = (&(*it));
    if (cursor == nullptr)
        std::cout<<"NULLOOOOOOOOOOOOOOOOOO"<<std::endl;
    return cursor;
}

void EditorGUI::removeCursor(qint32 siteId) {
    auto it = std::find_if(remoteCursors->begin(), remoteCursors->end(), [siteId](const RemoteCursor &c) {
        return (c.getSiteId() == siteId);
    });
    if (it != remoteCursors->end()) {
        remoteCursors->erase(it);
        std::cout << "Remove cursor " << siteId << std::endl;
        textEdit->update();
        emit setNumUsers(--nUsers);
    }
}

void EditorGUI::flushInsertQueue() {
    if (insertQueue.empty())
        return;

    QString s;
    while (!insertQueue.empty()) {
        s.push_back(insertQueue.front());
        insertQueue.pop();
    }
    insertText(posQueue, s, siteIdQueue);
    posLastChar = -1;
}

void EditorGUI::drawLabel(RemoteCursor *cursor) const{
    if(cursor->getSiteId() > 0) {
        if (cursor->labelTimer->isActive())
            cursor->labelTimer->stop();

        const QRect curRect = textEdit->cursorRect(*cursor);

        cursor->labelName->setParent(textEdit);
        cursor->labelName->show();
        cursor->labelName->move( std::min(curRect.left()+3,  int(textEdit->document()->pageSize().width())), curRect.top() -10);
        cursor->labelTimer->setParent(textEdit);
        cursor->labelTimer->start(5000);
    }
}

void EditorGUI::deleteAllText() {
    signalBlocker = !signalBlocker;
    emit clear();
    signalBlocker = !signalBlocker;
    remoteCursors->clear();
    emit setNumUsers(nUsers=0);
}

void EditorGUI::handleCursorPosChanged() {
    qint32 pos;
//    if(textEdit->textCursor().hasSelection()){
//        qint32 start = textEdit->textCursor().selectionStart();
//        qint32 end = textEdit->textCursor().selectionEnd();
//    }
    pos = textEdit->textCursor().position();
//    std::cout << "cursor index:" << pos << std::endl;
    if (model->getSiteId() != -1 && !myCursorPosUpdateBlocker) {
        model->sendCursorPos(pos);
    }
}

void EditorGUI::updateRemoteCursorPos(qint32 pos, qint32 siteId) {
    std::cout << "draw in " << pos << " siteID: " << siteId << std::endl;
    auto cursor = getRemoteCursor(siteId);
    cursor->setPosition(pos, QTextCursor::MoveAnchor);

    drawLabel(cursor);
    textEdit->update();
}

void EditorGUI::enableSendCursorPos() {
    myCursorPosUpdateBlocker = false;
}

void EditorGUI::highlight(qint32 pos, qint32 siteId) {
//    std::cout << "highlight " << pos << " siteId " << siteId << std::endl;
    auto cursor = getRemoteCursor(0);
//    auto format = QTextCharFormat();

//    if (!model->getHighlighting())
    auto format = getHighlightFormat(siteId);
//    else
//        format.setBackground(QColor("white"));
    signalBlocker = !signalBlocker;
    cursor->setPosition(pos , QTextCursor::MoveAnchor);
    cursor->setPosition(pos+1, QTextCursor::KeepAnchor);
    cursor->mergeCharFormat(format);
    signalBlocker = !signalBlocker;
}

void EditorGUI::keyPressEvent(QKeyEvent *e) {
    QWidget::keyPressEvent(e);
//    std::cout << "dentro keypress" << std::endl;
}

QTextCharFormat EditorGUI::getHighlightFormat(qint32 siteId) {
    auto format = QTextCharFormat();
    auto color = QColor();

    color.setNamedColor(RemoteCursor::getColor(siteId));
    color.setAlpha(124);
    format.setBackground(QBrush(color));

    return format;
}

void EditorGUI::exportToPdf() {
    if (!fileName.isEmpty()) {

        QString defaultName{};
        if (fileName.contains("/"))
            defaultName = fileName.replace("/", "_");
        else
            defaultName = fileName;
        QString name = QFileDialog::getSaveFileName(this, "Export PDF", defaultName, "*.pdf");
        if (!name.isEmpty()) {
            if (QFileInfo(name).suffix().isEmpty()) { name.append(".pdf"); }

            QPrinter printer(QPrinter::PrinterResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setPaperSize(QPrinter::A4);
            printer.setOutputFileName(name);
            textEdit->print(&printer);
        }
    }
}

void EditorGUI::highlightedTip(int pos, QPoint globalPos) {
    if(!model->getHighlighting()) return;
    auto sym = model->fromPosToSymbol(pos+1);
    qint32 siteId = sym.getSymId().getSiteId();
    auto i = file_writers.find(siteId);
    if( i != file_writers.end() )
        showToolTip(siteId, globalPos);
    else {
        lastToolTipPos = globalPos;
        emit userQuery(siteId);
    }
}

void EditorGUI::recordUserWriter(qint32 siteId, QString& user,bool connection){
    auto i = file_writers.find(siteId);
    if( i == file_writers.end() )
        file_writers.insert(std::make_pair(siteId,user)); // salvo in "cache"

    if(!connection)
        showToolTip(siteId,lastToolTipPos);
}

void EditorGUI::flushFileWriters() {
    file_writers.clear();
}

void EditorGUI::showToolTip(qint32 siteId, QPoint globalPos) {
    auto palette = QPalette();
    palette.setColor(QPalette::ToolTipBase,RemoteCursor::getColor(siteId));
    QToolTip::setPalette(palette);
    auto name = file_writers.find(siteId)->second;
    QToolTip::showText(globalPos,name, textEdit);
//    textEdit->showToolTip(siteId,globalPos,name);
}

void EditorGUI::setCharFormat(bool checked) {
    if (checked) {
//        std::cout << "setCharFormat true" << std::endl;
        textEdit->mergeCurrentCharFormat(getHighlightFormat(model->getSiteId()));
    }
    else {
//        std::cout << "setCharFormat false" << std::endl;
        auto format = QTextCharFormat();
        format.setBackground(QColor("white"));
        textEdit->mergeCurrentCharFormat(format);
    }
}

void EditorGUI::checkCharFormat(const QTextCharFormat &f) {
    if(highlightEditor)
        textEdit->mergeCurrentCharFormat(getHighlightFormat(model->getSiteId()));
}

void EditorGUI::setBold(bool checked) const {
    auto f = QTextCharFormat();
    if(checked)
        f.setFontWeight(QFont::Bold);
    else
        f.setFontWeight(QFont::Normal);
    textEdit->mergeCurrentCharFormat(f);
}

void EditorGUI::setItalic(bool checked) const {
    auto f = QTextCharFormat();
    f.setFontItalic(checked);
    textEdit->mergeCurrentCharFormat(f);
}

void EditorGUI::setUnderline(bool checked) const {
    auto f = QTextCharFormat();
    f.setFontUnderline(checked);
    textEdit->mergeCurrentCharFormat(f);
}
