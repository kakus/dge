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
    QLinkedList<WorldModel::SpQBodyDef> list = model->getBodyList();
    QVERIFY(list.count() == 0);
}

void WorldtestTest::cleanupTestCase()
{
}

void WorldtestTest::insertBody()
{
    QBodyDef *body = new QBodyDef;
    model->addBody(body);
    QLinkedList<WorldModel::SpQBodyDef> list = model->getBodyList();

    QVERIFY(list.count() == 1);
    QVERIFY(body == list.first().data());
}

void WorldtestTest::removeBody()
{

}

QTEST_APPLESS_MAIN(WorldtestTest)

#include "tst_worldtesttest.moc"
