#ifndef RANK
#define RANK

#include "cocos2d.h"
#include "SystemHead.h"
#include "BaseLayer.h"
#include "extensions/GUI/CCScrollView/CCTableView.h"
USING_NS_CC;
using namespace extension;
class RankShow : public BaseLayer ,public TableViewDataSource,public TableViewDelegate {
public:
	static Scene* createScene();
	bool init();

	CREATE_FUNC(RankShow);
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(TableView* table) override;
	virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;

	TableView* table1;

};

#endif