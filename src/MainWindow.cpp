/***********************************************************
 * 程序主窗口
 * 程序主界面
 *
 *
 * create by MasterFan
 *      on 2017年1月25日
 *
 *
 *
 ***********************************************************/

#include "src/MainWindow.h"
#include "ui_MainWindow.h"
#include <QMenu>
#include <QPainter>
#include <QPixmap>
#include <QCloseEvent>
#include <QDebug>
#include <QTextCodec>
#include <QPainterPath>
#include <QtMath>
#include <QPixmap>

#include "DialogGeneratePro.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    initialize();//初始化

    initSystemTrayIcon();//初始化托盘图标

    connectAction();//连接信号， 槽
}

/**
 * @brief 初始化
 * @return
 */
int MainWindow::initialize()
{
    // 不显示标题栏(亦无边框)
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);

    // 背景透明(全自画)
    setAttribute(Qt::WA_TranslucentBackground);

    dragging = false;

    //设置默认选中项
    ui->toolButtonGenerate->setChecked(true);
    ui->stackedWidget->setCurrentIndex(0);

    //添加几个可点击的自定义label标签【最小化， 关闭， 生成项目】
    addMFLabel();

    //设置整个界面的样式
    this->setStyleSheet(cssLoader.loadCss(":/styles/style/Main.css"));

    return 0;
}

/**
 * @brief 添加几个可点击的label标签【最小化， 关闭， 生成项目】
 */
void MainWindow::addMFLabel()
{
    //添加生成项目Label
    createLabel = new MFLabel(ui->stackedWidget->widget(0));//把createLabel添加到第一个面板中
    createLabel->setGeometry(300, 150, 171, 71);
    createLabel->setObjectName("labelGen");
    createLabel->setAlignment(Qt::AlignCenter);
    createLabel->setText("创建项目");
    createLabel->setFont(QFont("黑体",20,QFont::Bold));

    //最小化
    minimunLabel = new MFLabel(this);
    minimunLabel->setObjectName("mainMinimunLabel");
    minimunLabel->setGeometry(720, 10, 31, 31);
    QPixmap minimunIcon;
    minimunIcon.load(":/images/res/minimun.png");
    minimunLabel->setPixmap(minimunIcon);
    minimunLabel->setScaledContents(true);

    //最大化
    closeLabel = new MFLabel(this);
    closeLabel->setObjectName("mainCloseLabel");
    closeLabel->setGeometry(755, 10, 31, 31);
    QPixmap closeIcon;
    closeIcon.load(":/images/res/close.png");
    closeLabel->setPixmap(closeIcon);
    closeLabel->setScaledContents(true);
}

/**
 * @brief 连接信号， 槽
 * @return
 */
int MainWindow::connectAction()
{
    //托盘图标右键菜单
    connect(ui->actionTrayOpen,  SIGNAL(triggered()), this, SLOT(onTrayActionOpen()));
    connect(ui->actionTrayLogin, SIGNAL(triggered()), this, SLOT(onTrayActionLogin()));
    connect(ui->actionTrayExit,  SIGNAL(triggered()), this, SLOT(onTrayActionExit()));

    //4个主功能键
    connect(ui->toolButtonGenerate,  SIGNAL(clicked()), this, SLOT(onGenProClicked()));
    connect(ui->toolButtonConfig,    SIGNAL(clicked()), this, SLOT(onConfigClicked()));
    connect(ui->toolButtonAddWidget, SIGNAL(clicked()), this, SLOT(onAddWidgetClicked()));
    connect(ui->toolButtonAboutUs,   SIGNAL(clicked()), this, SLOT(onAboutClicked()));

    //最小化， 和关闭
    connect(minimunLabel, SIGNAL(clicked()), this, SLOT(onMinimunClicked()));
    connect(closeLabel,   SIGNAL(clicked()), this, SLOT(onCloseClicked()));

    connect(createLabel, SIGNAL(clicked()), this, SLOT(onGenLabelClicked()));

    return 0;
}

/**
 * @brief 最小化
 * @return
 */
int MainWindow::onMinimunClicked()
{
    this->showMinimized();
    return 0;
}

/**
 * @brief 关闭
 * @return
 */
int MainWindow::onCloseClicked()
{
    this->close();
    return 0;
}

/**
 * @brief 生成按钮点击
 * @return
 */
int MainWindow::onGenLabelClicked()
{
    DialogGeneratePro dialogGeneratePro(this);

    dialogGeneratePro.exec();
    qDebug() << "生成弹窗" ;
    return 0;
}


//边框画阴影
void MainWindow::paintEvent(QPaintEvent *event)
{
    int num = 10;
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(num, num, this->width()-20, this->height()-20);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 30);
    for(int i = 0; i < num; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(num - i, num - i, this->width() - (num - i) * 2, this->height() - (num - i) * 2);
        color.setAlpha(150 - qSqrt(i) * 50);
        painter.setPen(color);
        painter.drawPath(path);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{//鼠标移动
    if (event->buttons() & Qt::LeftButton)
    {
        if (dragging)
        {
            QPoint delta = event->globalPos() - startPosition;
            move(framePosition + delta);
        }
    }

    QWidget::mousePressEvent(event);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{//鼠标按下
    if (event->button() == Qt::LeftButton)
    {
        dragging = true;
        startPosition = event->globalPos();
        framePosition = frameGeometry().topLeft();//frameGeometry() //窗口离屏幕的位置
    }

    QWidget::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{//释放鼠标
    dragging = false;
    QWidget::mousePressEvent(event);
}

/**
 * @brief 设置选中项
 * @param position
 * @return
 */
int MainWindow::checkByLastPosition(int position)
{
    switch (position) {
    case 0:
    {
        ui->toolButtonGenerate->setChecked(true);
        ui->toolButtonConfig->setChecked(false);
        ui->toolButtonAddWidget->setChecked(false);
        ui->toolButtonAboutUs->setChecked(false);

        ui->stackedWidget->setCurrentIndex(0);
    }
        break;

    case 1:
        ui->toolButtonGenerate->setChecked(false);
        ui->toolButtonConfig->setChecked(true);
        ui->toolButtonAddWidget->setChecked(false);
        ui->toolButtonAboutUs->setChecked(false);

        ui->stackedWidget->setCurrentIndex(1);
        break;

    case 2:
        ui->toolButtonGenerate->setChecked(false);
        ui->toolButtonConfig->setChecked(false);
        ui->toolButtonAddWidget->setChecked(true);
        ui->toolButtonAboutUs->setChecked(false);

        ui->stackedWidget->setCurrentIndex(2);
        break;

    case 3:
        ui->toolButtonGenerate->setChecked(false);
        ui->toolButtonConfig->setChecked(false);
        ui->toolButtonAddWidget->setChecked(false);
        ui->toolButtonAboutUs->setChecked(true);

        ui->stackedWidget->setCurrentIndex(3);
        break;

    default:// -1

        break;
    }
}

int MainWindow::onGenProClicked()
{
    checkByLastPosition(0);
    return 0;
}

int MainWindow::onConfigClicked()
{
    checkByLastPosition(1);
    return 0;
}

int MainWindow::onAddWidgetClicked()
{
    checkByLastPosition(2);
    return 0;
}

int MainWindow::onAboutClicked()
{
    checkByLastPosition(3);
    return 0;
}

/**
 * @brief 初始化托盘图标
 * @return
 */
int MainWindow::initSystemTrayIcon()
{

    //设置托盘提示文字和图标
    trayIcon.setToolTip("个人知识库\n开发人员最佳工具");
    trayIcon.setIcon(QIcon(":/images/res/1484816114_Know.ico"));

    //添加右键菜单
    QMenu *menu = new QMenu();
    menu->addAction(ui->actionTrayOpen);
    menu->addAction(ui->actionTrayLogin);
    menu->addSeparator();//分隔线
    menu->addAction(ui->actionTrayExit);

    //托盘点击
    connect(&trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onSystemTrayClicked(QSystemTrayIcon::ActivationReason)));

    //显示托盘
    trayIcon.setContextMenu(menu);
    trayIcon.show();

    return 0;
}

//----------The tray context menu slots-----------
//退出主程序
int MainWindow::onTrayActionExit()
{
    QApplication::exit(0);
    return 0;
}

//登录窗口显示
int MainWindow::onTrayActionLogin()
{
    qDebug() << "打开主界面";
    return 0;
}

//打开主界面
int MainWindow::onTrayActionOpen()
{
    this->showNormal();
    return 0;
}
//----------end tray context menu slots-----------

//托盘点击处理
int MainWindow::onSystemTrayClicked(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::Trigger || reason == QSystemTrayIcon::DoubleClick)
    {
        this->showNormal();
    }
    return 0;
}

/**
 * @brief 关闭事件
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}

/**
 * @brief 回收
 */
MainWindow::~MainWindow()
{
    delete ui;
}
