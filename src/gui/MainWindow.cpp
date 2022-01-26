#include <iostream>
#include <fstream>
#include <streambuf>
#include <thread>
#include <chrono>

#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include "SQLHighLighter.h"
#include "RAHighLighter.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("RATSQL"));
    setFixedSize(1000, 700);

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
    // TODO - CMakelists.txt post-build command // todo wa is deze todo pablo?
    std::ifstream file("resources/styleSheet.qss");
    if (!file.is_open()) { std::cerr << "styleSheet can't be opened\n"; }
    std::string styleSheet((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    ui->centralwidget->setStyleSheet(QString::fromStdString(styleSheet));

    // Editor
    mTextEdit = new TextEdit(this);
    mTextEdit->setHighLighter(new RAHighLighter(mTextEdit));
    mOutputTextEdit = new TextEdit(this, true);
    mOutputTextEdit->setHighLighter(new SQLHighLighter(mOutputTextEdit));
    ui->layoutTextEdit->addWidget(mTextEdit);
    ui->layoutTextEdit->addWidget(mOutputTextEdit);

    // Menu bar

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

    // TODO - post-build cmakelists resources kopieren naar targets
    // Parser
    mCFG = std::make_shared<CFG>("input/grammar.json");
    mLexer = std::make_unique<Lexer>(mCFG->getAliasMap(), mCFG->getAliases());
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
        connect(a, SIGNAL(clicked(QString)), mTextEdit, SLOT(onCharacterAdded(QString)));
        mCharacters.emplace_back(a);
        ui->gridChards->addWidget(a, row, column);
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
    auto createButton = [this](const std::string& name, int row, int column) -> SettingButton* {
        SettingButton* s = new SettingButton(QString::fromStdString(name), this);
        mSettings.emplace_back(s);
        ui->gridSettings->addWidget(s, row, column);
        return s;
    };
    auto er = createButton("Error correction", 0, 0);
    connect(er, SIGNAL(clicked(bool)), mTextEdit, SLOT(onErrorDetection(bool)));
    auto* erDeviation = new QLineEdit("1", this);
    erDeviation->setMaxLength(1);
    erDeviation->setValidator(new QIntValidator(0, 10, erDeviation));
    ui->gridSettings->addWidget(erDeviation, 0, 1);
    mSettings.emplace_back(erDeviation);
    connect(erDeviation, SIGNAL(textChanged(QString)), mTextEdit, SLOT(onDeviation(QString)));

    auto opt = createButton("Optimizer", 1, 0);
    connect(opt, SIGNAL(clicked(bool)), mTextEdit, SLOT(onOptimize(bool)));

    auto nm = createButton("Naming conventions", 2, 0);
    connect(nm, SIGNAL(clicked(bool)), mTextEdit, SLOT(onNamingConventions(bool)));
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

    // Show error message if expression is empty
    if (query.empty())
    {
        createMessageBox(QMessageBox::Critical, QString("Error"), QString("Error: given regular expression is empty."),
                         QMessageBox::Ok);
    }

    mEarlyParser = std::make_unique<EarleyParser>(mCFG);

    const auto& tokens = mLexer->tokenise(query);
    const auto& tree = mEarlyParser->earleyParse(tokens);


    std::string SQL = tree->translate();

    std::cout << SQL << "\n";

    mOutputTextEdit->clear();
    mOutputTextEdit->insertPlainText(QString::fromStdString(SQL));
}

