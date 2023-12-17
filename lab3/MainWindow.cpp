#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_mainLayout = new QVBoxLayout();
    m_controlLayout = new QHBoxLayout();

    m_eventTitleEdit = new QLineEdit(this);
    m_eventTitleEdit->setPlaceholderText("Enter event title here...");

    m_eventDateEdit = new QDateEdit(this);
    m_eventDateEdit->setMinimumDate(QDate(2023, 1, 1));

    m_addEventButton = new QPushButton("Add calendar event", this);
    m_removeEventButton = new QPushButton("Remove last event", this);

    m_eventsWidget = new QWidget(this);
    m_eventsWidgetLayout = new QVBoxLayout();

    m_eventsWidget->setLayout(m_eventsWidgetLayout);

    m_mainLayout->addWidget(m_eventTitleEdit);
    m_mainLayout->addWidget(m_eventDateEdit);
    m_controlLayout->addWidget(m_addEventButton);
    m_controlLayout->addWidget(m_removeEventButton);
    m_mainLayout->addLayout(m_controlLayout);
    m_mainLayout->addWidget(m_eventsWidget);

    auto centralWidget = new QWidget(this);
    centralWidget->setLayout(m_mainLayout);
    this->setCentralWidget(centralWidget);

    QObject::connect(m_addEventButton, &QPushButton::clicked, this, &MainWindow::addEventCalendar);
    QObject::connect(m_removeEventButton, &QPushButton::clicked, this, &MainWindow::removeCalendarEvent);
}

MainWindow::~MainWindow() {}

void MainWindow::addEventCalendar()
{
    QLabel *event = new QLabel(this);

    auto title = m_eventTitleEdit->text();

    if(title.isEmpty())
    {
        title = QString("Empty title");
    }

    title += " ";
    title += m_eventDateEdit->text();
    event->setText(title);

    m_eventsWidgetLayout->addWidget(event);
}

void MainWindow::removeCalendarEvent()
{
    int widgetCount = m_eventsWidgetLayout->count();

    if(widgetCount > 0)
    {
        QLayoutItem *item = m_eventsWidgetLayout->takeAt(widgetCount - 1);
        delete item->widget();
        delete item;
    }
}
