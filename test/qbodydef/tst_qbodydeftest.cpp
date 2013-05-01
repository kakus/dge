#include <QString>
#include <QtTest>
#include "qbodydef.h"

class QbodydefTest : public QObject
{
    Q_OBJECT
    
public:
    QbodydefTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();
    void testCase1();
};

QbodydefTest::QbodydefTest()
{
}

void QbodydefTest::initTestCase()
{
    QBodyDef bodyDef;
}

void QbodydefTest::cleanupTestCase()
{
}

void QbodydefTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(QbodydefTest)

#include "tst_qbodydeftest.moc"
