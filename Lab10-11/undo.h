#ifndef UNDO_H
#define UNDO_H

#include <vector>
#include "domain.h"
#include "repo.h"

class UndoAction {
public:
	virtual void doUndo() = 0;
	virtual ~UndoAction() {};
};

class UndoAdd : public UndoAction {
	Offer offer;
	Repo* repo;
public:
	UndoAdd(Repo* repo, const Offer& offer) : repo{ repo }, offer{ offer } {};
	void doUndo() override {
		repo->delete_offer_repo(offer.getName(), offer.getDestination());
	}
	~UndoAdd() = default;
};

class UndoDelete : public UndoAction {
	Offer offer;
	Repo* repo;
public:
	UndoDelete(Repo* repo, const Offer offer) : repo{ repo }, offer{ offer } {};
	void doUndo() override {
		repo->add_offer_repo(offer);
	}
	~UndoDelete() = default;
};

class UndoModify : public UndoAction {
	Offer offer;
	Repo* repo;
public:
	UndoModify(Repo* repo, const Offer offer) : repo{ repo }, offer{ offer } {};
	void doUndo() override {
		repo->update_offer_repo(offer.getName(), offer.getDestination(), offer.getPrice());
	}
	~UndoModify() = default;
};
#endif // !undo.