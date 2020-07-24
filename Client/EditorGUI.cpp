//
// Created by Windows on 25/03/2020.
//

#include <QtGui/QPainter>
#include "EditorGUI.h"

EditorGUI::EditorGUI(SharedEditor *model, QWidget *parent) : QMainWindow(parent) {
    signalBlocker = false;
    setModel(model);
    setUpGUI();
    setWindowTitle(QCoreApplication::applicationName());
    posLastChar = -1;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EditorGUI::flushInsertQueue);
    timer->start(200); //tra 150 e 200 dovrebbe essere ottimale
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
    statusBar = new QStatusBar(this);
    textEdit = new QTextEdit(this);
    toolBar = new QToolBar("Toolbar", this);

    statusBar->showMessage("StatusBar");

//    aggiungo gli elementi alla finestra
    this->setCentralWidget(textEdit);
    this->setStatusBar(statusBar);
    this->addToolBar(toolBar);
    toolBar->setMovable(false);

    setupFileActions();
    menuBar()->addMenu("&Options");

    textEdit->setFocus();
    setCurrentFileName(QString());

//    imposto la grandezza della finestra
    auto size = QGuiApplication::primaryScreen()->size();
    this->resize(size.width() * 0.7, size.height() * 0.7);

    connect(textEdit->document(), &QTextDocument::contentsChange, this, &EditorGUI::contentsChange);
    connect(textEdit, &QTextEdit::copyAvailable, this, &EditorGUI::setSelected);
//    load("./file.txt");
    loadSymbols();
}


bool EditorGUI::load(const QString &f) {
    QString f1 = R"(C:\Users\Windows\Documents\POLITO\Programmazione di sistema\Progetto\MyTest\file.txt)";
    if (!QFile::exists(f1)) {
        std::cout << "File non esiste";
        return false;
    }
    QFile file(f1);

    if (!file.open(QFile::ReadOnly)) {
        std::cout << "File non aperto";
        return false;
    }

    QTextStream in(&file);
    QString str = in.readAll();
//    QByteArray data = file.readAll();
//    QTextCodec *codec = Qt::codecForHtml(data);
//    QString str = codec->toUnicode(data);
//    textEdit->setPlainText(QString::fromUtf8(data));
    textEdit->setPlainText(str);
    setCurrentFileName(f);
    return true;
}


void EditorGUI::loadSymbols() {
    signalBlocker = !signalBlocker;
    textEdit->setText(model->to_string());
    signalBlocker = !signalBlocker;
}

void EditorGUI::setupFileActions() {
//    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    QAction *a = menu->addAction(tr("&New"), this, &EditorGUI::fileNew);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
//    tb->addAction(a);

    a = menu->addAction(tr("&Open..."), this, &EditorGUI::fileOpen);
    a->setShortcut(QKeySequence::Open);
//    tb->addAction(a);

    menu->addSeparator();

    actionSave = menu->addAction(tr("&Save"), this, &EditorGUI::fileSave);
    actionSave->setShortcut(QKeySequence::Save);
    actionSave->setEnabled(false);
//    tb->addAction(actionSave);

    a = menu->addAction(tr("Save &As..."), this, &EditorGUI::fileSaveAs);
    a->setPriority(QAction::LowPriority);
    menu->addSeparator();

    a = menu->addAction(tr("&Quit"), this, &EditorGUI::close);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);

}

void EditorGUI::setupEditActions() {
    //TODO
}

void EditorGUI::setupTextActions() {
    //TODO
}

void EditorGUI::setCurrentFileName(const QString &filename) {
    this->fileName = filename;
    textEdit->document()->setModified(false);

    QString showName;
    if (fileName.isEmpty())
        showName = "untitled.txt";
    else
        showName = QFileInfo(fileName).fileName();

    setWindowTitle(showName + " - " + QCoreApplication::applicationName());
    setWindowModified(false);
}

void EditorGUI::setModel(SharedEditor *_model) {
    this->model = _model;
}

void EditorGUI::contentsChange(int pos, int charsRemoved, int charsAdded) {
    int i = 0;
    if (!signalBlocker) {
        auto blocks = textEdit->document()->blockCount();
        auto pages = textEdit->document()->pageCount();
        std::cout << "Numero blocchi: " << blocks << " Numero pagine: " << pages << std::endl;
        if (!selected && pos == 0 && charsRemoved > 0 && charsAdded > 1) {
            charsAdded -= charsRemoved;
            charsRemoved = 0;
        } else if (selected && pos == 0 && charsRemoved > 0 && charsAdded > 1) {
            charsRemoved--;
            charsAdded--;
        }
        if (charsRemoved > 0) {  //sono stati cancellati dei caratteri
            std::cout << "Cancellazione carattere " << pos << std::endl;
            for (i = 0; i < charsRemoved; i++) {
                model->localErase(pos);
            }
        }
        if (charsAdded > 0) {  //sono stati aggiunti caratteri
            std::cout << "Inserimento carattere " << pos << std::endl;
            for (i = 0; i < charsAdded; i++) {
                model->localInsert(pos + i, textEdit->document()->characterAt(pos + i));
            }
        }
    }
}

void EditorGUI::insertText(qint32 pos, const QString &value, qint32 siteId) {
    pos--;
    RemoteCursor *cursor;

    cursor = getRemoteCursor(siteId);

//    std::cout << "position:" << pos << std::endl;
    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    cursor->insertText(value);
    std::cout << "Inseriti " << value.size() << " caratteri in " << pos << std::endl;
    signalBlocker = !signalBlocker;
    drawCursor(cursor);
    updateRemoteCursors(siteId,pos, Message::insertion);
}

bool EditorGUI::checkSiteId(RemoteCursor &rc, qint32 siteId) {
    return rc.getSiteId() == siteId;
}

void EditorGUI::deleteText(qint32 pos, qint32 siteId, qint32 n) {
    pos--;
    RemoteCursor *cursor;

    cursor = getRemoteCursor(siteId);

//    std::cout << "position:" << pos << std::endl;
    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    cursor->setPosition(pos + n, QTextCursor::KeepAnchor);
    signalBlocker = !signalBlocker;
    cursor->removeSelectedText();
    std::cout << "Rimosso " << pos << std::endl;
    signalBlocker = !signalBlocker;
    drawCursor(cursor);
    updateRemoteCursors(siteId,pos, Message::removal);
}


void EditorGUI::updateSymbols(qint32 pos, QString s, qint32 siteId, Message::action_t action) {
    if (action == Message::removal) {
//        flushInsertQueue();     //prima della delete inserisco eventuali caratteri in coda
        deleteText(pos, siteId, s.size());
    } else {
        insertText(pos, s, siteId);
//        if(posLastChar<0 || pos!=posLastChar+1) {
//            flushInsertQueue();
//            posQueue = pos;
//            siteIdQueue = siteId;
//        }
//        insertQueue.push(value);
//        posLastChar = pos;
    }
}

void EditorGUI::updateRemoteCursors(qint32 siteId, int pos, Message::action_t action) {
    // aggiorno la posizione degli altri cursori

    for (auto it = remoteCursors.begin(); it != remoteCursors.end(); it++) {
        if (it->getSiteId() != siteId) {
            drawCursor(&(*it));
//            auto newPosition = it->position();
//            if (newPosition > pos) {
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
//    std::cout << "Lista siteId dei cursori remoti:" << std::endl;
//    std::for_each(remoteCursors.begin(), remoteCursors.end(), [](RemoteCursor& rc){std::cout << rc.getSiteId() << std::endl;});
    auto it = std::find_if(remoteCursors.begin(), remoteCursors.end(), [siteId](const RemoteCursor &c) {
        std::cout << "SiteId: " << c.getSiteId() << std::endl;
        return (c.getSiteId() == siteId);
    });
    if (it == remoteCursors.end()) {
        remoteCursors.emplace_back(textEdit->document(), siteId);
        cursor = &remoteCursors.back();
    } else
        cursor = (&(*it));


    return cursor;
}

void EditorGUI::removeCursor(qint32 siteId) {
    if (!remoteCursors[siteId].isNull()) {
        remoteCursors.erase(remoteCursors.begin() + siteId);
    }
}


void EditorGUI::fileNew() {
//    TODO
}

void EditorGUI::fileOpen() {
//    TODO
}

void EditorGUI::fileSave() {
//    TODO
}

void EditorGUI::fileSaveAs() {
//    TODO
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

void EditorGUI::drawCursor(RemoteCursor *cursor){
    // Obtain rectangle of 'real' cursor
    // and the biggest font that can be contained
    const QRect curRect = textEdit->cursorRect(*cursor);
    auto width = curRect.width();
    auto height = curRect.height();
//    std::cout << width<<"x"<<height<<std::endl;

//    QPainter painter(this->textEdit);
//    painter.setPen(Qt::red);
//    painter.drawRect(curRect);

        QFont bigFont=this->font();
    bigFont.setPixelSize(curRect.height());
    QFontMetrics bigFontInfo(bigFont);

//     Obtain size of current font
    QFont thisFont=this->font();
    thisFont.setPointSize(textEdit->fontPointSize());
    QFontMetrics thisFontInfo(thisFont);
    int thisFontHeight=thisFontInfo.height();

//     Obtain a rectangle that encloses the char, aligned to
//     the bottom of the 'real' cursor rectangle
    QRect thisRect=thisFontInfo.boundingRect(curRect, Qt::AlignBottom, "I");

//     Calculate where is the baseline of the current char
//     with respect to the one of the biggest char
    int biggerBaseline=curRect.bottom()-bigFontInfo.descent();
    int thisBaseline=thisRect.bottom()-thisFontInfo.descent();
    int baseLineDiff=abs(thisBaseline-biggerBaseline);

    int ty=thisRect.bottom()-thisFontInfo.descent()-thisFontHeight*0.85-baseLineDiff;


    cursor->labelName->setParent(textEdit);
    cursor->labelCursor->setParent(textEdit);
    cursor->labelName->show();
    cursor->labelCursor->show();
    cursor->labelName->move(curRect.left()+width+2, ty-5);
//            curRect.top()-5);
    cursor->labelCursor->move(curRect.left()-2,curRect.top());
}