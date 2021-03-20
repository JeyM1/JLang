//
// Created by Denis Afendikov on 18.03.2021.
//

#ifndef _BTREENODE_H_
#define _BTREENODE_H_

#include <memory>
#include <vector>


template < class T >
class BTreeNode
{
	T _value;

	std::shared_ptr<BTreeNode<T>> _left;
	std::shared_ptr<BTreeNode<T>> _right;

  public:
	explicit BTreeNode( const T& value ) : _value(value) {}

	T value() const { return _value; }

	const std::shared_ptr<BTreeNode<T>>& left() const {
		return _left;
	}

	void setLeft( const T& val ) {
		_left = std::make_shared<BTreeNode>(val);
	}

	const std::shared_ptr<BTreeNode<T>>& right() const {
		return _right;
	}

	void setRight( const T& val ) {
		_right = std::make_shared<BTreeNode>(val);
	}

};

#endif //_BTREENODE_H_
