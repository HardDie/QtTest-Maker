#ifndef GUIWORKER_H
#define GUIWORKER_H

#include <QObject>

#include "testworker.h"

class GUIWorker : public QObject
{
    Q_OBJECT
public:
    explicit GUIWorker(QObject *parent = nullptr);

signals:
    void setTestString(QString text, QString index);
    void returnToMainMenu();

public slots:
    void setTestModeQA();
    void setTestModeAQ();
    void setTestModeMix();

    void setTestModeTypeQA();
    void setTestModeTypeAQ();
    void setTestModeTypeMix();

    void nextTestStep();

private:
    TestWorker _testWorker;
};

#endif // GUIWORKER_H
