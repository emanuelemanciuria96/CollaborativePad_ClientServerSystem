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
#include <QtWidgets/QColorDialog>
#include <QTextBlock>

QVector<QString> fonts{"Arial","Arial Black","Comic Sans MS", "Courier","Georgia","Impact","Tahoma","Times New Roman","Trebuchet MS","Verdana"};

bool EditorGUI::isModifying = false;

EditorGUI::EditorGUI(SharedEditor *model, QWidget *parent) : QWidget(parent){
    remoteCursors = std::make_shared<std::list<RemoteCursor>>();
    signalBlocker = false;
    myCursorPosUpdateBlocker = false;
    setModel(model);
    setUpGUI();
    posLastChar = -1;
    timer = new QTimer(this);
    curBlockerTimer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EditorGUI::enableSendCursorPos);
    //connect(timer, &QTimer::timeout, this, &EditorGUI::flushInsertQueue);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this,&EditorGUI::handleCursorPosChanged);
    connect(textEdit, &MyTextEdit::tipRequest, this,&EditorGUI::highlightedTip);
    connect(textEdit, &QTextEdit::currentCharFormatChanged, this, &EditorGUI::currentCharFormatChanged);
    connect(textEdit, &MyTextEdit::updateLabels, this, &EditorGUI::updateLabels);
    connect(textEdit, &QTextEdit::selectionChanged, this, &EditorGUI::selectionChanged);
    connect(textEdit,&MyTextEdit::isPastingAtFirst,[this](){ isPastingAtFirst = true; });
    timer->start(200); //tra 150 e 200 dovrebbe essere ottimale
    textEdit->setFontFamily("Times New Roman");
    textEdit->setFontPointSize(12);
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
    textEdit = new MyTextEdit(remoteCursors, model,this);
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

    connect(this, SIGNAL(clear()), textEdit, SLOT(clear()));

    stylestring= "QTextEdit{border-style:none}"
                    "QScrollBar:vertical {background:white; width:8px; margin: 0px 0px 0px 0px;}"
                    "QScrollBar::handle:vertical {background: #C3C3C3; border:0px solid lightgray; border-radius:4px; min-height: 20px;}"
//                  "QScrollBar::add-line:vertical{height:0px; subcontrol-position: bottom; subcontrol-origin: margin;"
//                  "QScrollBar::sub-line:vertical {height: 0px width:0px; subcontrol-position: top; subcontrol-origin: margin; "
                    "QScrollBar:horizontal {background:white; height:8px; margin: 0px 0px 0px 0px;}"
                    "QScrollBar::handle:horizontal {background: #C3C3C3; border:0px solid lightgray; border-radius: 4px; min-height: 20px;}";
    textEdit->setStyleSheet(stylestring);
    textEdit->setFocus();

    connect(textEdit->document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(contentsChange(int, int, int)));
    connect(textEdit, &QTextEdit::copyAvailable, this, &EditorGUI::setSelected);

}

void EditorGUI::setCurrentFileName(QString& filename) {
    this->fileName = filename;
}

void EditorGUI::setModel(SharedEditor* _model) {
    this->model = _model;
}

//chiamata quando si effettuano modifiche sul editor
void EditorGUI::contentsChange(int pos, int charsRemoved, int charsAdded) {
//    std::cout << "dentro contentsChange" << std::endl;
    if( isModifying ){
        isModifying = false;
        return;
    }
    if(alignmentCommand){
        alignmentCommand=false;
        return;
    }

    int i = 0;
    if (!signalBlocker) {
        myCursorPosUpdateBlocker = true;
        curBlockerTimer->start(500);
//        std::cout << "contents change " << std::endl;

        if( isPastingAtFirst && charsAdded > 0){
            charsAdded-=charsRemoved;
            charsRemoved = 0;
            isPastingAtFirst = false;
            textEdit->document()->clearUndoRedoStacks();
        }

        //std::cout << "invio caratteri" << std::endl;
        if (charsRemoved > 0) {  //sono stati cancellati dei caratteri
            //std::cout << "Cancellazione carattere " << index << std::endl;
            model->localErase(pos,charsRemoved);
            if (textEdit->toPlainText().isEmpty()) {
                auto curs = textEdit->textCursor();
                curs.setPosition(0);
                textEdit->setAlignment(Qt::AlignLeft);
                textEdit->setFontFamily("Times New Roman");
                textEdit->setFontPointSize(12);
            }
        }
        if (charsAdded > 0) {  //sono stati aggiunti caratteri
//            std::cout << "Inserimenti " << charsAdded << std::endl;
            for (i = 0; i < charsAdded; i++) {
                QChar ch = textEdit->document()->characterAt(pos+i);
                auto cursor = textEdit->textCursor();
                cursor.setPosition(pos+i+1);
                auto format = cursor.charFormat();
                auto blockFormat = cursor.blockFormat();
                auto align = blockFormat.alignment();
                format.setFontPointSize(format.font().pointSizeF()<=0? format.font().pixelSize() : format.font().pointSizeF());
                if(fonts.indexOf(format.fontFamily())<0) {
                    format.setFontFamily(fonts[7]);
                    cursor.movePosition(QTextCursor::Left,QTextCursor::KeepAnchor,1);
                    cursor.setCharFormat(format);
                }

                format.setBackground(QColor("white"));
                model->localInsert(pos+i, ch , format, align);
            }
            if(highlightIsActive) {
                highlight(pos, charsAdded, model->getSiteId(), *getRemoteCursor(0));
            }else{
//                textEdit->selectAll();
                auto cursor = textEdit->textCursor();
                int cursPos = cursor.position();
                cursor.setPosition(pos);
                cursor.movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,pos+charsAdded);
                auto format = QTextCharFormat();
                format.setBackground(Qt::white);
                cursor.mergeCharFormat(format);
                cursor.setPosition(cursPos);
                this->textEdit->setTextCursor(cursor);
            }
        }
        if(highlightIsActive)
            textEdit->document()->clearUndoRedoStacks();
        updateLabels();
    }
    model->undoredoAction();
//    std::cout << "fuori contentsChange" << std::endl;
}

void EditorGUI::textFormatChange(int pos, int charsModified) {

    int i=0;
    for(; i<charsModified; i++ ){
        auto cursor = getRemoteCursor(0);
        cursor->setPosition(pos+i+1);
        auto format = cursor->charFormat();
        format.setBackground(QBrush("white"));
        model->localModification(pos+i,format);
    }
}

void EditorGUI::insertText(qint32 pos, const QString &value, qint32 siteId, const QTextCharFormat& format) {
    pos--;
    RemoteCursor *cursor;
    cursor = getRemoteCursor(siteId);
//    std::cout << "Inseriti da siteId: " << siteId << std::endl;
    ///blocco l'invio della posizione del mio cursore quando ricevo modifiche
    myCursorPosUpdateBlocker = true;
    curBlockerTimer->start(500);
    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    cursor->setCharFormat(format);
    if(highlightIsActive)
        cursor->mergeCharFormat(getHighlightFormat(siteId));

    cursor->insertText(value);
    //std::cout << "Inseriti " << value.size() << " caratteri in " << index << std::endl;
    signalBlocker = !signalBlocker;
    drawLabel(cursor);
    updateLabels();
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
    drawLabel(cursor);
    if (textEdit->toPlainText().isEmpty()) {
        auto curs = textEdit->textCursor();
        curs.setPosition(0);
        alignmentCommand = true;
        textEdit->setAlignment(Qt::AlignLeft);
        textEdit->setFontFamily("Times New Roman");
        textEdit->setFontPointSize(12);
        updateLabels();
    }
//    updateLabels(siteId,index, Message::removal);
}

//chiamata quando si ricevono modifiche
void EditorGUI::updateSymbols(qint32 pos, const QString &s, qint32 siteId, QTextCharFormat& format, Message::action_t action) {
//    std::cout<<"updateSymbols inizio" << std::endl;
    if (action == Message::modification){
//        std::cout<<" -- stringa modificata: "<<s.toStdString()<<std::endl;
        auto curs = getRemoteCursor(0);
        curs->setPosition(pos-1);
        int numChars = s.size();
        curs->movePosition(QTextCursor::Right,QTextCursor::KeepAnchor,numChars);
        if( highlightIsActive ){
            format.clearBackground();
        }
        isModifying = true;
        curs->mergeCharFormat(format);
        qDebug()<<"merge";
        updateLabels();
    }
    else if (action == Message::removal) {
        deleteText(pos, siteId, s.size());
    } else {
//        std::cout<<" -- stringa inserita: "<<s.toStdString()<<std::endl;
        insertText(pos, s, siteId, format);
    }
    if(highlightIsActive)
        textEdit->document()->clearUndoRedoStacks();
}

void EditorGUI::updateAlignment(int pos, Qt::Alignment a) {

    auto curs = getRemoteCursor(0);
    curs->setPosition(pos);
    QTextBlockFormat frmt = curs->blockFormat();
    frmt.setAlignment(a);
    alignmentCommand = true;
    curs->setBlockFormat(frmt);

    textEdit->document()->clearUndoRedoStacks();
    updateLabels();

}

void EditorGUI::updateLabels() {
    // aggiorno la posizione degli altri cursori
    for (auto & remoteCursor : *remoteCursors) {
        if (remoteCursor.getSiteId() != model->getSiteId() && remoteCursor.getSiteId()>0) {
            if(!remoteCursor.labelName->isHidden())
                drawLabel(&remoteCursor);
        }
    }
}

RemoteCursor *EditorGUI::getRemoteCursor(qint32 siteId) {
    RemoteCursor *cursor;
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
    return cursor;
}

void EditorGUI::removeCursor(qint32 siteId) {
    auto it = std::find_if(remoteCursors->begin(), remoteCursors->end(), [siteId](const RemoteCursor &c) {
        return (c.getSiteId() == siteId);
    });
    if (it != remoteCursors->end()) {
        remoteCursors->erase(it);
        //std::cout << "Remove cursor " << siteId << std::endl;
        textEdit->update();
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
    insertText(posQueue, s, siteIdQueue, QTextCharFormat{});
    posLastChar = -1;
}

void EditorGUI::drawLabel(RemoteCursor *cursor) const{
//    std::cout << "dentro drawLabel ";
    if(cursor->getSiteId() > 0 && cursor->getSiteId()!= model->getSiteId()) {
        if (cursor->labelTimer->isActive())
            cursor->labelTimer->stop();

        const QRect curRect = textEdit->cursorRect(*cursor);
//        std::cout << "rect x: " << curRect.x() << std::endl;
        cursor->labelName->setParent(textEdit);
        cursor->labelName->show();
//        cursor->labelName->move( std::min(curRect.left()+3,  int(textEdit->document()->pageSize().width())), curRect.top() -10);
        cursor->labelName->move( curRect.left()+3, curRect.top() -10);
        cursor->labelTimer->setParent(textEdit);
        cursor->labelTimer->start(5000);
    }
}

void EditorGUI::deleteAllText() {
    signalBlocker = !signalBlocker;
    emit clear();
    signalBlocker = !signalBlocker;
    remoteCursors->clear();
    textEdit->setFontUnderline(false);
    textEdit->setFontItalic(false);
    textEdit->setFontWeight(0);
    textEdit->setTextColor(Qt::black);
    textEdit->setFontFamily("Times New Roman");
    textEdit->setFontPointSize(12);
}

void EditorGUI::handleCursorPosChanged() {
    qint32 pos = textEdit->textCursor().position();
//    std::cout << "cursor index:" << pos << std::endl;
    if (model->getSiteId() != -1 && !myCursorPosUpdateBlocker) {
        model->sendCursorPos(pos);
    }
}

void EditorGUI::updateRemoteCursorPos(qint32 pos, qint32 siteId) {
//    std::cout << "draw in " << pos << " siteID: " << siteId << std::endl;
    auto cursor = getRemoteCursor(siteId);
    cursor->setPosition(pos, QTextCursor::MoveAnchor);

    drawLabel(cursor);
    textEdit->update();
}

void EditorGUI::enableSendCursorPos() {
    myCursorPosUpdateBlocker = false;
}

void EditorGUI::loadHighlights(bool checked) {
//    std::cout<<"inizio highlight" << std::endl;
    auto i = 0;
    qint32 lastSiteId = -1;
    qint32 firstPos;
    qint32 n = 0;
    highlightIsActive = checked;
    auto cursor = getRemoteCursor(0);
    signalBlocker = !signalBlocker;
    cursor->beginEditBlock();
    if(checked) {
        for (auto s : model->getSiteIds()) {
            if (s == lastSiteId) {
                n++;
            } else {
                if (lastSiteId != -1)
                    highlight(firstPos, n, lastSiteId, *cursor);
                lastSiteId = s;
                firstPos = i;
                n = 1;
            }
            i++;
        }
        highlight(firstPos,n,lastSiteId, *cursor);
    }
    else{
        highlight(0,model->getSiteIds().size(),-1, *cursor);
    }
    cursor->endEditBlock();
    signalBlocker = !signalBlocker;
}

void EditorGUI::highlight(qint32 pos, qint32 n, qint32 siteId, QTextCursor& cursor) const {
    if(textEdit->textCursor().hasSelection()){
        auto newCursor = textEdit->textCursor();
        newCursor.setPosition(newCursor.position(),QTextCursor::MoveAnchor);
        textEdit->setTextCursor(newCursor);
    }
    if(n>0) {
//        std::cout << "dentro highlight " << std::endl;
        auto format = QTextCharFormat();

        if (siteId != -1) {
            format = getHighlightFormat(siteId);
            textEdit->mergeCurrentCharFormat(format);
        } else {
            format.setBackground(QColor("white"));
            textEdit->mergeCurrentCharFormat(format);
        }

//    std::cout << "dentro setPosition " << std::endl;
        cursor.setPosition(pos, QTextCursor::MoveAnchor);
        cursor.setPosition(pos + n, QTextCursor::KeepAnchor);
//    std::cout << "dentro merge " << std::endl;
        cursor.mergeCharFormat(format);
//    std::cout << "fuori highlight " << std::endl;
    }
}

void EditorGUI::keyPressEvent(QKeyEvent *e) {
    QWidget::keyPressEvent(e);
//    std::cout << "dentro keypress" << std::endl;
}

QTextCharFormat EditorGUI::getHighlightFormat(qint32 siteId) {
    auto format = QTextCharFormat();
    auto color = QColor();

    color.setNamedColor(RemoteCursor::getColorHex(siteId));
    color.setAlpha(124);
    format.setBackground(color);

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
    if(!highlightIsActive) return;
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

void EditorGUI::showToolTip(qint32 siteId, QPoint globalPos) {
    auto textColor = QString();
    auto color = RemoteCursor::getColorHex(siteId);
    auto style = stylestring;
    RemoteCursor::isDarkColor(QColor(color)) ? textColor = "white"  : textColor = "black";

    style.append("QToolTip {color: "+textColor + ";background-color: " + color + "; border: 1px solid darkgray;}");
    textEdit->setStyleSheet(style);
//    QToolTip::setPalette(palette);
    auto name = file_writers.find(siteId)->second;
    QToolTip::showText(globalPos,name, textEdit);
//    textEdit->showToolTip(siteId,globalPos,name);
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

void EditorGUI::setBold(bool checked) {
    auto f = QTextCharFormat();
    if(checked)
        f.setFontWeight(QFont::Bold);
    else
        f.setFontWeight(QFont::Normal);
    if(isTextSelected)
        isModifying = true;
    textEdit->mergeCurrentCharFormat(f);
    if(isTextSelected){
        auto curs = textEdit->textCursor();
        int pos = curs.selectionStart();
        int numChars = curs.selectionEnd()-pos;
        textFormatChange(pos,numChars);
    }
}

void EditorGUI::setItalic(bool checked) {
    auto f = QTextCharFormat();
    f.setFontItalic(checked);
    if(isTextSelected)
        isModifying = true;
    if(isTextSelected)
        isModifying = true;
    textEdit->mergeCurrentCharFormat(f);
    if(isTextSelected){
        auto curs = textEdit->textCursor();
        int pos = curs.selectionStart();
        int numChars = curs.selectionEnd()-pos;
        textFormatChange(pos,numChars);
    }
}

void EditorGUI::setUnderline(bool checked) {
    auto f = QTextCharFormat();
    f.setFontUnderline(checked);
    if(isTextSelected)
        isModifying = true;
    if(isTextSelected)
        isModifying = true;
    textEdit->mergeCurrentCharFormat(f);
    if(isTextSelected){
        auto curs = textEdit->textCursor();
        int pos = curs.selectionStart();
        int numChars = curs.selectionEnd()-pos;
        textFormatChange(pos,numChars);
    }
}

void EditorGUI::selectionChanged() {
    if(textEdit->textCursor().hasSelection())
        hasSelection = true;
    else
        hasSelection = false;
//    std::cout << "selection " << hasSelection << std::endl;
}


void EditorGUI::textSize(const QString &p)
{
    qreal pointSize = p.toFloat();
    if (p.toFloat() > 0) {
        QTextCharFormat fmt;
        fmt.setFontPointSize(pointSize);
        if(isTextSelected)
            isModifying = true;
        textEdit->mergeCurrentCharFormat(fmt);
        if(isTextSelected){
            auto curs = textEdit->textCursor();
            int pos = curs.selectionStart();
            int numChars = curs.selectionEnd()-pos;
            textFormatChange(pos,numChars);
        }
    }
}

void EditorGUI::textFamily(const QString &f)
{
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    if(isTextSelected)
        isModifying = true;
    textEdit->mergeCurrentCharFormat(fmt);
    if(isTextSelected){
        auto curs = textEdit->textCursor();
        int pos = curs.selectionStart();
        int numChars = curs.selectionEnd()-pos;
        textFormatChange(pos,numChars);
    }
}

void EditorGUI::textColor()
{
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    if(isTextSelected)
        isModifying = true;
    textEdit->mergeCurrentCharFormat(fmt);
    if(isTextSelected){
        auto curs = textEdit->textCursor();
        int pos = curs.selectionStart();
        int numChars = curs.selectionEnd()-pos;
        textFormatChange(pos,numChars);
    }


    emit colorChanged(col);
}

void EditorGUI::currentCharFormatChanged(const QTextCharFormat &format)
{
    emit fontChanged(format.font());
    emit colorChanged(format.foreground().color());
}

void EditorGUI::setAbsoluteAlignment(int pos, QFlags<Qt::AlignmentFlag> a, bool selection) {
    short action;
    if( a & Qt::AlignLeft){
        action = 0;
    }
    if( a & Qt::AlignRight){
        action = 2;
    }
    if( a & Qt::AlignHCenter){
        action = 4;
    }
    if( a & Qt::AlignJustify){
        action = 8;
    }

    textEdit->document()->clearUndoRedoStacks();
    alignmentCommand = true;
    if(!selection) {
        auto cursor = textEdit->textCursor();
        int tmpPos = cursor.position();
        cursor.setPosition(pos);
        textEdit->setTextCursor(cursor);
        textEdit->setAlignment(a | Qt::AlignAbsolute);
        cursor.setPosition(tmpPos);
        textEdit->setTextCursor(cursor);
        int indexBlock=textEdit->document()->findBlock(tmpPos).position();
        model->localAlignment(indexBlock,action);
    }else{
        int start=textEdit->textCursor().selectionStart();
        int end=textEdit->textCursor().selectionEnd();
        QHash<int, int> blocks;
        for(int i=start;i<=end;i++){
            int indexBlock=textEdit->document()->findBlock(i).position();
            blocks[indexBlock]=action;
        }
        textEdit->setAlignment(a|Qt::AlignAbsolute);

        QHash<int,int>::const_iterator i = blocks.constBegin();
        while (i != blocks.constEnd()) {
            model->localAlignment(i.key(),i.value());
            ++i;
        }
    }
}

void EditorGUI::setStyleInFirstPosition() {
    auto cursor = textEdit->textCursor();
    if (cursor.position() == 0 && cursor.block().text().isEmpty()){
        textEdit->setFontFamily("Times New Roman");
        textEdit->setFontPointSize(12);
    }

}
