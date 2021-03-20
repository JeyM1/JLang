//
// Created by Denis Afendikov on 20.03.2021.
//

#ifndef _BTREE_H_
#define _BTREE_H_

#include <memory>
#include "BTreeNode.h"


template < class T >
class BTree
{
	std::shared_ptr<BTreeNode<T>> _root;

  public:
	BTree() {}

	const std::shared_ptr<BTreeNode<T>>& root() const {
		return _root;
	}

	void setRoot( const T& val ) {
		_root = std::make_shared<BTreeNode>(val);
	}
};

#endif //_BTREE_H_
