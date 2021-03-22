//
// Created by Denis Afendikov on 20.03.2021.
//

#ifndef _TREE_H_
#define _TREE_H_

#include <memory>
#include "TreeNode.h"


template < class T >
class Tree
{
	std::shared_ptr<TreeNode<T>> _root;

  public:
	Tree() = default;

	const std::shared_ptr<TreeNode<T>>& root() const {
		return _root;
	}

	void setRoot( std::shared_ptr<TreeNode<T>> ptr ) {
		_root = ptr;
	}
};

#endif //_TREE_H_
