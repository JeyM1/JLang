//
// Created by Denis Afendikov on 18.03.2021.
//

#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <memory>
#include <vector>


template < class T >
class TreeNode
{
	T _value;

  public:
	std::shared_ptr<TreeNode<T>> left;
	std::shared_ptr<TreeNode<T>> operand;
	std::shared_ptr<TreeNode<T>> right;

  public:
	explicit TreeNode( const T& value ) : _value(value) {}

	TreeNode(
		T value,
		const std::shared_ptr<TreeNode<T>>& left = nullptr,
		const std::shared_ptr<TreeNode<T>>& operand = nullptr,
		const std::shared_ptr<TreeNode<T>>& right = nullptr
	) : _value(value), left(left), operand(operand), right(right) {}

	T value() const { return _value; }

};

#endif //_TREENODE_H_
