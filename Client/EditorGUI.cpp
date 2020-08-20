//
// Created by Windows on 25/03/2020.
//

#include <QtGui/QPainter>
#include "EditorGUI.h"

EditorGUI::EditorGUI(SharedEditor *model, QWidget *parent) : QWidget(parent){
    signalBlocker = false;
    setModel(model);
    setUpGUI();
    setWindowTitle(QCoreApplication::applicationName());
    posLastChar = -1;
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &EditorGUI::flushInsertQueue);
    connect(textEdit, &QTextEdit::cursorPositionChanged, this,&EditorGUI::handleCursorPosChanged);
    timer->start(200); //tra 150 e 200 dovrebbe essere ottimale
}


void EditorGUI::setUpGUI() {
//    inizializzo gli elementi
//    setupFileActions();
    textEdit = new MyTextEdit(&remoteCursors,this);
    setLayout(new QVBoxLayout(this));
    this->layout()->addWidget(textEdit);
    this->layout()->setContentsMargins(0,0,0,0);

    connect(this,SIGNAL(clear()),textEdit,SLOT(clear()));

    textEdit->setFocus();
    setCurrentFileName(QString());

    connect(textEdit->document(), SIGNAL(contentsChange(int, int, int)), this, SLOT(contentsChange(int,int,int)));
    connect(textEdit, &QTextEdit::copyAvailable, this, &EditorGUI::setSelected);
//    load("./file.txt");
    loadSymbols();
}


bool EditorGUI::load(const QString &f) {
    QString f1 = R"(C:\Users\Windows\Documents\POLITO\Programmazione di sistema\Progetto\MyTest\file.txt)";
    if(!QFile::exists(f1)){
        std::cout << "File non esiste";
        return false;
    }
    QFile file(f1);

    if(!file.open(QFile::ReadOnly)) {
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

/*
void EditorGUI::setupFileActions() {
//    QToolBar *tb = addToolBar(tr("File Actions"));
    QMenu *menu = menuBar()->addMenu(tr("&File"));

    QAction *a = menu->addAction(tr("&New"),this,&EditorGUI::fileNew);
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
*/

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
    if(fileName.isEmpty())
        showName = "untitled.txt";
    else
        showName = QFileInfo(fileName).fileName();

    setWindowTitle(showName + " - " + QCoreApplication::applicationName());
    setWindowModified(false);
}

void EditorGUI::setModel(SharedEditor* _model) {
    this->model = _model;
}

//chiamata quando si effettuano modifiche sul editor
void EditorGUI::contentsChange(int pos, int charsRemoved, int charsAdded) {
    int i = 0;
    if (!signalBlocker) {
        auto blocks = textEdit->document()->blockCount();
        auto pages = textEdit->document()->pageCount();
//        std::cout << "Numero blocchi: " << blocks << " Numero pagine: " << pages << std::endl;
        if (!selected && pos == 0 && charsRemoved > 0 && charsAdded > 1) {
            charsAdded -= charsRemoved;
            charsRemoved = 0;
        } else if (selected && pos == 0 && charsRemoved > 0 && charsAdded > 1) {
            charsRemoved--;
            charsAdded--;
        }
        if (charsRemoved > 0) {  //sono stati cancellati dei caratteri
            //std::cout << "Cancellazione carattere " << index << std::endl;
            for (i = 0; i < charsRemoved; i++) {
                model->localErase(pos);
            }
            updateRemoteCursors(model->getSiteId(),pos,Message::removal);
        }
        if (charsAdded > 0) {  //sono stati aggiunti caratteri
            //std::cout << "Inserimento carattere " << index << std::endl;
            for (i = 0; i < charsAdded; i++) {
                model->localInsert(pos + i, textEdit->document()->characterAt(pos + i));
            }
//            updateRemoteCursors(model->getSiteId(),index,Message::insertion);
        }
    }
}

void EditorGUI::insertText(qint32 pos, const QString &value, qint32 siteId) {
    pos--;
    RemoteCursor *cursor;

    cursor = getRemoteCursor(siteId);

//    std::cout << "position:" << index << std::endl;
    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    signalBlocker = !signalBlocker;
    cursor->insertText(value);
//    textEdit->update();
//    drawLabel(cursor);
    //std::cout << "Inseriti " << value.size() << " caratteri in " << index << std::endl;
    signalBlocker = !signalBlocker;
//    updateRemoteCursors(siteId,index, Message::insertion);
}

bool EditorGUI::checkSiteId(RemoteCursor &rc, qint32 siteId) {
    return rc.getSiteId() == siteId;
}

void EditorGUI::deleteText(qint32 pos, qint32 siteId, qint32 n) {
    pos--;
    QTextCursor *cursor;

    cursor = getRemoteCursor(siteId);

//    std::cout << "position:" << index << std::endl;
    cursor->setPosition(pos, QTextCursor::MoveMode::MoveAnchor);
    cursor->setPosition(pos + n, QTextCursor::KeepAnchor);
    signalBlocker = !signalBlocker;
    cursor->removeSelectedText();
    //std::cout << "Rimosso " << index << std::endl;
    signalBlocker = !signalBlocker;
//    updateRemoteCursors(siteId,index, Message::removal);
}

//chiamata quando si ricevono modifiche
void EditorGUI::updateSymbols(qint32 pos, QString s, qint32 siteId, Message::action_t action) {
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
}

void EditorGUI::updateRemoteCursors(qint32 mySiteId, int pos, Message::action_t action) {
    // aggiorno la posizione degli altri cursori

    for (auto & remoteCursor : remoteCursors) {
        if (remoteCursor.getSiteId() != mySiteId) {
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
//    std::cout << "Lista siteId dei cursori remoti:" << std::endl;
    auto it = std::find_if(remoteCursors.begin(), remoteCursors.end(), [siteId](const RemoteCursor &c) {
        std::cout << "SiteId: " << c.getSiteId() << std::endl;
        return (c.getSiteId() == siteId);
    });
    if (it == remoteCursors.end()) {
        remoteCursors.emplace_back(textEdit->document(), siteId);
        cursor = &remoteCursors.back();
        connect(cursor->labelTimer, &QTimer::timeout, cursor->labelName, &QLabel::hide);
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

void EditorGUI::drawLabel(RemoteCursor *cursor){
    if (cursor->labelTimer->isActive())
        cursor->labelTimer->stop();

    const QRect curRect = textEdit->cursorRect(*cursor);

    cursor->labelName->setParent(textEdit);
    cursor->labelName->show();
    cursor->labelName->move(curRect.left()+5,curRect.top()-5);
    connect(cursor->labelTimer, &QTimer::timeout, cursor->labelName, &QLabel::hide);
    cursor->labelTimer->start(5000);
}

void EditorGUI::deleteAllText() {
    signalBlocker = !signalBlocker;
    emit clear();
    signalBlocker = !signalBlocker;
}

void EditorGUI::handleCursorPosChanged() {
    qint32 pos;
    pos = textEdit->textCursor().position();
    std::cout << "cursor index:" << pos << std::endl;
    if (model->getSiteId() != -1) {
        model->sendCursorPos(pos);
    }
}

void EditorGUI::updateRemoteCursorPos(qint32 pos, qint32 siteId) {
    std::cout << "draw in " << pos << " siteID: " << siteId << std::endl;
    if (siteId > 0) {
        auto cursor = getRemoteCursor(siteId);
        cursor->setPosition(pos, QTextCursor::MoveAnchor);
        textEdit->update();
        drawLabel(cursor);
    }

}
