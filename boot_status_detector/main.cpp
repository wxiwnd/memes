#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QVBoxLayout>
#include <cmath>
#include <QStyleFactory>

class BootChecker : public QWidget
{
    Q_OBJECT
public:
    BootChecker()
    {
        setWindowTitle("电脑开机状态检测器");
        setFixedSize(440, 280);

        const char *fontFamily = "Helvetica, Arial, sans-serif";

        auto *title = new QLabel("电脑开机状态检测器");
        title->setAlignment(Qt::AlignCenter);
        title->setStyleSheet(QString("font: 18pt '%1';").arg(fontFamily));

        auto *subtitle = new QLabel("使用先进的大数据技术分析您的电脑状态");
        subtitle->setAlignment(Qt::AlignCenter);
        subtitle->setStyleSheet(
            QString("color: gray; font: 10pt '%1';").arg(fontFamily));

        btnDetect = new QPushButton("开始检测");
        btnDetect->setFixedSize(160, 48);
        btnDetect->setStyleSheet(QString("font: 12pt '%1';").arg(fontFamily));

        progress = new QProgressBar;
        progress->setStyle(QStyleFactory::create("Fusion"));
        progress->setRange(0, 100);
        progress->setValue(0);
        progress->setVisible(false);
        progress->setFixedHeight(24);
        progress->setTextVisible(true);
        progress->setFormat("%p%");

        result = new QLabel;
        result->setAlignment(Qt::AlignCenter);
        result->setStyleSheet(
            QString("font: bold 14pt '%1'; color: #2b8a3e;").arg(fontFamily));

        auto *lay = new QVBoxLayout(this);
        lay->addWidget(title);
        lay->addWidget(subtitle);
        lay->addStretch();
        lay->addWidget(btnDetect, 0, Qt::AlignHCenter);
        lay->addWidget(progress);
        lay->addStretch();
        lay->addWidget(result);

        connect(btnDetect, &QPushButton::clicked,
                this, &BootChecker::startFakeCheck);

        timer = new QTimer(this);
        connect(timer, &QTimer::timeout,
                this, &BootChecker::stepProgress);
    }

private slots:
    void startFakeCheck()
    {
        btnDetect->setEnabled(false);
        result->clear();

        progress->setValue(0);
        progress->setVisible(true);

        step  = 0;
        ticks = 120;
        timer->start(40);
    }

    void stepProgress()
    {
        if (++step > ticks) {
            timer->stop();
            progress->setVisible(false);
            result->setText("恭喜你，你的电脑当前为开机状态！");
            btnDetect->setEnabled(true);
            return;
        }

        double t = double(step) / ticks;
        double eased = (t < 0.5)
                       ? 4 * std::pow(t, 3)
                       : 1 - std::pow(-2 * t + 2, 3) / 2;

        progress->setValue(int(eased * 100));
    }

private:
    QPushButton  *btnDetect;
    QProgressBar *progress;
    QLabel       *result;
    QTimer       *timer;

    int step  = 0;
    int ticks = 120;
};

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    BootChecker w;
    w.show();
    return app.exec();
}

#include "main.moc"
