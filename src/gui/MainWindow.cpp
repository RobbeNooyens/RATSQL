#include <iostream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <chrono>
#include <sstream>
#include <regex>
#include <QTextStream>

#include "MainWindow.h"
#include "../io/CommandHandler.h"
#include "./ui_MainWindow.h"
#include "aboutdialog.h"

#include "SQLHighLighter.h"
#include "RAHighLighter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("RATSQL"));

    // Create menu + other things
    init();
}

MainWindow::~MainWindow()
{
    for (const auto& i : mCharacters) { delete i; }
    for (const auto &i : mSettings) { delete i; }
    mCharacters.clear();
    mSettings.clear();
    delete ui;
}

void MainWindow::init()
{
    // Central widget
    this->setCentralWidget(ui->centralwidget);
    std::ifstream file("resources/styleSheet.qss");
    if (!file.is_open()) { std::cerr << "styleSheet can't be opened\n"; }
    std::string styleSheet((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    ui->centralwidget->setStyleSheet(QString::fromStdString(styleSheet));
    ui->centralwidget->setAutoFillBackground(true);
    setStyleSheet("background-color: rgb(32, 32, 35);");

    // Editor
    mTextEdit = new TextEdit(this);
    mTextEdit->setHighLighter(new RAHighLighter(mTextEdit));
    mOutputTextEdit = new TextEdit(this, true);
    mOutputTextEdit->setHighLighter(new SQLHighLighter(mOutputTextEdit));
    ui->mInput->addWidget(mTextEdit);
    ui->mOutput->addWidget(mOutputTextEdit);

    // Logo


    // Menu bar
    createMenu();
    createAction();

    // Settings
    ui->mGridSettings->setVerticalSpacing(3);
    createSettingButtons();

    // Characters
    createCharButtons();

    // Convert button
    ui->mButtonConvert->setText(QString("CONVERT"));
//    ui->mButtonConvert->setFixedSize(100, 30);
    connect(ui->mButtonConvert, SIGNAL(clicked()), this, SLOT(onConvertBtnClicked()));

    mSys = std::make_unique<System>();
}

void MainWindow::createMenu()
{
    ui->menuBar->setNativeMenuBar(false);

    mAbout = new QMenu("About", this);
    ui->menuBar->addMenu(mAbout);

    mFile = new QMenu("File", this);
    ui->menuBar->addMenu(mFile);
}

void MainWindow::createAction()
{
    mAboutAct = new QAction("About", this);
    connect(mAboutAct, SIGNAL(triggered()), this, SLOT(onAboutAct()));
    mAbout->addAction(mAboutAct);

    mSaveAct = new QAction("Save", this);
    connect(mSaveAct, SIGNAL(triggered()), this, SLOT(onSaveAct()));
    mFile->addAction(mSaveAct);

    mOpenAct = new QAction("Open", this);
    connect(mOpenAct, SIGNAL(triggered()), this, SLOT(onOpenAct()));
    mFile->addAction(mOpenAct);
}

void MainWindow::createCharButtons()
{
    /**
     * @brief Lambda function for inserting character buttons into gridChars
     * @param character std::wstring - special character
     * @param row int - row where button needs to be placed
     * @param column int - column where button needs to placed
     */
    auto createButton = [this](const std::wstring& character, int row, int column) -> void {
        CharButton* a = new CharButton(QString::fromStdWString(character), this);
        a->setFixedSize(QSize(30, 30));
        connect(a, SIGNAL(clicked(QString)), mTextEdit, SLOT(onCharacterAdded(QString)));
        mCharacters.emplace_back(a);
        ui->mGridChars->addWidget(a, row, column);
    };
    // Special characters / symbols
    createButton(L"π", 0, 0);
    createButton(L"σ", 0, 1);
    createButton(L"ρ", 0, 2);
    createButton(L"→", 0, 3);
    createButton(L"←", 0, 4);
    createButton(L"∧", 0, 5);
    createButton(L"∨", 0, 6);
    createButton(L"¬", 0, 7);
    createButton(L"≠", 0, 8);
    createButton(L"=", 0, 9);
    createButton(L"≥", 0, 10);
    createButton(L"≤", 1, 0);
    createButton(L">", 1, 1);
    createButton(L"<", 1, 2);

    // Operators
    createButton(L"∩", 1, 3);
    createButton(L"∪", 1, 4);
    createButton(L"/", 1, 5);
    createButton(L"-", 1, 6);
    createButton(L"⨯", 1, 7);
    createButton(L"⨝", 1, 8);

    // Misc
    createButton(L"{", 1, 9);
    createButton(L"}", 1, 10);
    createButton(L"(", 2, 0);
    createButton(L")", 2, 1);
    createButton(L".", 2, 2);
    createButton(L",", 2, 3);
    createButton(L"'", 2, 4);
}

void MainWindow::createSettingButtons()
{
    auto createButton = [this](const std::string& name, int row, int column) -> SettingButton* {
        SettingButton* s = new SettingButton(QString::fromStdString(name), this);
        mSettings.emplace_back(s);
        ui->mGridSettings->addWidget(s, row, column);
        return s;
    };
    auto er = createButton("Error correction", 0, 0);
    connect(er, SIGNAL(clicked(bool)), mTextEdit, SLOT(onErrorDetection(bool)));
    auto* erDeviation = new QLineEdit("1", this);
    erDeviation->setMaxLength(1);
    erDeviation->setFixedSize(30,20);
    erDeviation->setValidator(new QIntValidator(0, 10, erDeviation));
    ui->mGridSettings->addWidget(erDeviation, 0, 1);
    mSettings.emplace_back(erDeviation);
    connect(erDeviation, SIGNAL(textChanged(QString)), mTextEdit, SLOT(onDeviation(QString)));

    auto opt = createButton("Optimizer", 1, 0);
    connect(opt, SIGNAL(clicked(bool)), mTextEdit, SLOT(onOptimize(bool)));
//
//    auto nm = createButton("Naming conventions", 2, 0);
//    connect(nm, SIGNAL(clicked(bool)), mTextEdit, SLOT(onNamingConventions(bool)));
}

QMessageBox* MainWindow::createMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
                                QMessageBox::StandardButton button)
{
    auto* msg = new QMessageBox(icon, title, text, button);
    auto* horizontalSpacer = new QSpacerItem(250, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    auto* layout = (QGridLayout*)msg->layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msg->exec();
    return msg;
}

void MainWindow::onConvertBtnClicked()
{
    // Regular expression
    std::string query = mTextEdit->toPlainText().toStdString();

    bool correction = mTextEdit->isErrorDetection();
    int deviation = mTextEdit->getDeviation();
    bool optimized = mTextEdit->isOptimized();
    bool namingConventions = mTextEdit->isNamingConventions();

    std::vector<std::vector<ParseToken>> tokens;

    #if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
    auto stringList = mTextEdit->toPlainText().split(QRegularExpression("[\r\n]"));
    #else
    auto stringList = mTextEdit->toPlainText().split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    #endif
    for(auto& s: stringList) {
        string str = s.toStdString();
        tokens.push_back(mSys->tokenize(str));
    }

    std::vector<std::vector<ParseToken>> optimizedRA;

    if(optimized) {
        for(auto& row: tokens) {
            for(auto& optimizedRow: mSys->optimize(row)){
                optimizedRA.push_back(optimizedRow);
            }
        }
    } else {
        for(auto& row: tokens) {
            optimizedRA.push_back(row);
        }
    }

    // OptimzedRA back to the mTextEdit
    QString lines;
    for(auto& expression: optimizedRA) {
        std::stringstream combined;
        for(auto& token: expression) {
            combined << token.getContent() << " ";
        }
        combined << endl;
        lines.push_back(QString::fromStdString(combined.str()));
    }
    mTextEdit->setText(lines);


    // Show error message if expression is empty
    if (query.empty())
    {
        createMessageBox(QMessageBox::Critical, QString("Error"), QString("Error: given regular expression is empty."),
                         QMessageBox::Ok);

    } else {
//        // Else, parse the input
//        std::string SQL = mSys->convertToSQL(query);
//        mOutputTextEdit->clear();
//        mOutputTextEdit->insertPlainText(QString::fromStdString(SQL));
    }
}

void MainWindow::onAboutAct()
{
//    QMessageBox::about(this, QString("About"), QString("RATSQL created by Robbe, Cedric, Maarten and Pablo.\nCopyright © 2022 RATSQL."));
    AboutDialog a(nullptr);
    a.exec();
}

void MainWindow::onSaveAct()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save output"), "", tr("sql (*.sql)"));
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox msg;
        createMessageBox(QMessageBox::Critical, QString("Error"), QString("Error while saving file."),
                         QMessageBox::Ok);
        return;
    }
    QTextStream out(&file);
    std::string output;
    out << mOutputTextEdit->toPlainText();
    file.close();
}

void MainWindow::onOpenAct()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"));
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox msg;
        createMessageBox(QMessageBox::Critical, QString("Error"), QString("Error while opening file."),
                         QMessageBox::Ok);
        return;
    }
    mTextEdit->clear();
    QTextStream in(&file);
    while(!in.atEnd()) {
        QString line = in.readLine();
        mTextEdit->append(line);
    }
    file.close();
    file.close();
}

