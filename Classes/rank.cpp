#include "rank.h"
#pragma execution_character_set("utf-8")
#include <sstream>
Scene* RankShow::createScene() {
	auto s = Scene::create();
	auto l = RankShow::create();
	s->addChild(l);
	return s;
}
bool RankShow::init() {
	if (!BaseLayer::init()) {
		return false;
	}
	auto sp = Sprite::create("rank.jpg");
	sp->setAnchorPoint(Vec2(0.5, 0.5));
	sp->setPosition(Vec2(0, 0));
	Size sz = Director::getInstance()->getVisibleSize();
	table1 = TableView::create(this, Size(300, 400), sp);
	table1->setDelegate(this);
	table1->setAnchorPoint(Vec2(0.5, 0.5));
	table1->setPosition(Vec2(sz.width/2, 300));
	
	addChild(table1);
	//table->reloadData();//開始運行上面的配置

	return true;
}

TableViewCell* RankShow::tableCellAtIndex(TableView* table, ssize_t idx) {
	//顯示內容在這//修改在這裡
	TableViewCell* cell = table->dequeueCell();
	int sz = table->getViewSize().height;
	if (!cell) {
		cell = TableViewCell::create();
	}
	if (idx == 0) {
		std::string s = FileUtils::getInstance()->getStringFromFile(CSV_FILE_PATH);
		std::istringstream chaos(s);
		std::string source;
		std::vector<int> vec;
		while (std::getline(chaos, source)) {
			size_t pos = source.find("score:");
			if (pos != std::string::npos) {
				std::string sco = source.substr(pos + 6);
				vec.push_back(std::stoi(sco));
			}
		}
		std::sort(vec.begin(), vec.end(), std::greater<int>());
		for (auto& c : vec) {
			log("%d", c);
		}
		int index = 0;
		
		for (auto& c : vec) {
			index;
			std::string str = StringUtils::format("第%d名:分數:%d", index + 1, c);
			Label* label = Label::createWithTTF(str, "fonts/msjh.ttc", 34);
			label->setAnchorPoint(Vec2(0.5, 0.5));
			label->setPosition(Vec2(150, sz - 50 - index * 50));
			cell->addChild(label, 1);
			index++;
			if (index > 5) {
				break;
			}
		}
	}


	return cell;
}
ssize_t RankShow::numberOfCellsInTableView(TableView* table) {
	//重複框格
	return 1;
}
void RankShow::tableCellTouched(TableView* table, TableViewCell* cell) {
	int idx = cell->getIdx();
	log("%d", idx);
}