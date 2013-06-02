#include <QString>
#include <QtTest>
#include "worldmodel.h"

class WorldtestTest : public QObject
{
    Q_OBJECT
    
public:
    WorldtestTest();
    
private Q_SLOTS:
    void initTestCase();
    void insertBody();
    void removeBody();
    void cleanupTestCase();

private:
    WorldModel *model;
};

WorldtestTest::WorldtestTest()
{
}

void WorldtestTest::initTestCase()
{
    model = new WorldModel;
    auto list = model->getBodies();
    QVERIFY(list.count() == 0);
}

void WorldtestTest::cleanupTestCase()
{
    for (auto &qbody: model->getBodies())
        model->removeBody(dynamic_cast<QBodyDef*>(qbody));


    QVERIFY(model->getBodies().count() == 0);
}

void WorldtestTest::insertBody()
{
    QBodyDef *body = new QBodyDef;
    auto cr8_body = model->createBody(body);
    auto list = model->getBodies();

    QVERIFY(list.count() == 1);
    QVERIFY(body != (list.first()));
    QVERIFY(cr8_body == (list.first()));
}

void WorldtestTest::removeBody()
{
    QBodyDef *b_created[20];

    for (int i=0; i<20; ++i)
        b_created[i] = model->createBody();

    int s = qrand()%19;
    int i = s + 1;

    for (; i != s; i = (i+1)%20)
    {
        model->removeBody(b_created[i]);
        for (auto &qbody: model->getBodies())
            QVERIFY(qbody != b_created[i]);
    }
}

QTEST_APPLESS_MAIN(WorldtestTest)

#include "tst_worldtesttest.moc"
