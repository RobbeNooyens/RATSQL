#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <iostream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <chrono>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("RATSQL"));
    setFixedSize(1000, 700);


    // TODO // TODO: wa is deze todo pablo?
    mTextEdit = new TextEdit;

    ui->layoutTextEdit->addWidget(mTextEdit);

    // Create menu + other things
    createMenu();
}

MainWindow::~MainWindow()
{

    for (const auto& i : mCharacters) { delete i; }
    for (const auto &i : mSettings) { delete i; }
    mCharacters.clear();
    mSettings.clear();
    delete ui;
}

void MainWindow::createMenu()
{
    // Central widget
    this->setCentralWidget(ui->centralwidget);
    // TODO - CMakelists.txt post-build command // todo wa is deze todo pablo?
    std::ifstream file("resources/styleSheet.qss");
    if (!file.is_open()) { std::cerr << "styleSheet can't be opened\n"; }
    std::string styleSheet((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    ui->centralwidget->setStyleSheet(QString::fromStdString(styleSheet));

    // Menu bar


    // Text editor - input
//    ui->textEditInput->setReadOnly(false);
//    ui->textEditInput->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->textEditInput->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->textEditInput->setPlaceholderText(tr("Start typing your Regular Expression ..."));

    // Text editor - output
//    ui->textEditOutput->setReadOnly(true);
//    ui->textEditOutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->textEditOutput->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    ui->textEditOutput->setPlaceholderText(tr("SQL output ..."));

    // Convert button
    ui->buttonConvert->setText(QString("CONVERT"));
    connect(ui->buttonConvert, SIGNAL(clicked()), this, SLOT(onConvertBtnClicked()));

    // Settings
    ui->gridSettings->setVerticalSpacing(3);
    createSettingButtons();

    // Characters
    ui->gridChards->setHorizontalSpacing(1);
    ui->gridChards->setVerticalSpacing(1);
    createCharButtons();
}

void MainWindow::createCharButtons()
{
    /**
     * @brief Lambda function for inserting character buttons into gridChars
     * @param character std::wstring - special character
     * @param row unsigned int - row where button needs to be placed
     * @param column unsigned int - column where button needs to placed
     */
    auto createButton = [this](const std::wstring& character, unsigned int row, unsigned int column) -> void {
        CharButton* a = new CharButton(QString::fromStdWString(character), this);
        connect(a, SIGNAL(clicked(QString)), mTextEdit, SLOT(onCharacterAdded(QString)));
        mCharacters.emplace_back(a);
        ui->gridChards->addWidget(a, row, column);
    };
    // Special characters / symbols
    createButton(L"π", 0, 0);
    createButton(L"σ", 0, 1);
    createButton(L"ρ", 0, 2);
    createButton(L"->", 0, 3);
    createButton(L"<-", 0, 4);
    createButton(L"∧", 0, 5);
    createButton(L"∨", 0, 6);
    createButton(L"¬", 0, 7);
    createButton(L"≠", 0, 8);
    createButton(L"=", 0, 9);
    createButton(L"≥", 0, 10);
    createButton(L"≤", 0, 11);
    createButton(L">", 0, 12);
    createButton(L"<", 0, 13);

    // Operators
    createButton(L"∩", 1, 0);
    createButton(L"∪", 1, 1);
    createButton(L"/", 1, 2);
    createButton(L"-", 1, 3);
    createButton(L"⨯", 1, 4);
    createButton(L"⨝", 1, 5);

    // Misc
    createButton(L"{", 1, 6);
    createButton(L"}", 1, 7);
    createButton(L"(", 1, 8);
    createButton(L")", 1, 9);
    createButton(L".", 1, 10);
    createButton(L",", 1, 11);
    createButton(L"'", 1, 12);
}

void MainWindow::createSettingButtons()
{
    auto createButton = [this](const std::string& name, unsigned int row, unsigned int column) -> SettingButton* {
        SettingButton* s = new SettingButton(QString::fromStdString(name), this);
        mSettings.emplace_back(s);
        ui->gridSettings->addWidget(s, row, column);
        return s;
    };
    auto er = createButton("Error correction", 0, 0);
    connect(er, SIGNAL(clicked(bool)), mTextEdit, SLOT(onErrorDetection(bool)));

    auto opt = createButton("Optimizer", 1, 0);
    connect(opt, SIGNAL(clicked(bool)), mTextEdit, SLOT(onOptimize(bool)));

    auto nm = createButton("Naming conventions", 2, 0);
    connect(nm, SIGNAL(clicked(bool)), mTextEdit, SLOT(onNamingConventions(bool)));
}

QMessageBox* MainWindow::createMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
                                QMessageBox::StandardButton button)
{
    QMessageBox* msg = new QMessageBox(icon, title, text, button);
    QSpacerItem* horizontalSpacer = new QSpacerItem(250, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
    QGridLayout* layout = (QGridLayout*)msg->layout();
    layout->addItem(horizontalSpacer, layout->rowCount(), 0, 1, layout->columnCount());
    msg->exec();
    return msg;
}

void MainWindow::onConvertBtnClicked()
{
    // Regular expression
    std::string expr = mTextEdit->toPlainText().toStdString();

    // Show error message if expression is empty
    if (expr.empty())
    {
        createMessageBox(QMessageBox::Critical, QString("Error"), QString("Error: given regular expression is empty."),
                         QMessageBox::Ok);
    }

    // TODO - errors terugkrijgen van parser // todo wa is deze todo pablo?

//    ui->textEditOutput->clear();
//    ui->textEditOutput->insertPlainText(QString::fromStdString(expr));
}

