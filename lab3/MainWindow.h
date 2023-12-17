#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QDateEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_controlLayout;

    QLineEdit *m_eventTitleEdit;
    QDateEdit *m_eventDateEdit;

    QPushButton *m_addEventButton;
    QPushButton *m_removeEventButton;

    QWidget *m_eventsWidget;
    QVBoxLayout *m_eventsWidgetLayout;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void addEventCalendar();
    void removeCalendarEvent();
};
#endif // MAINWINDOW_H
