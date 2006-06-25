#ifndef SGE_BSP_TREE_HPP_INCLUDED
#define SGE_BSP_TREE_HPP_INCLUDED

#include <stdexcept>
#include "../math/rect.hpp"
#include "../math/dim.hpp"
#include "../math/point.hpp"

namespace sge
{

template<typename Size> class bsp_tree {
public:
	typedef Size size_type;
	typedef basic_point<size_type> point_type;
	typedef basic_dim<size_type> dim_type;
	typedef basic_rect<size_type> value_type;
	typedef const value_type& const_reference;
private:
	struct node {
		node(const value_type& rect, node* const parent, node* const left = 0, node* const right = 0)
			: rect(rect), parent(parent), left(left), right(right)
		{}

		~node()
		{
			if(parent)
			{
				if(parent->left == this)
					parent->left = 0;
				else
					parent->right = 0;
			}
			delete right;
			delete left;
		}

		friend bool operator==(const node& l, const node& r)
		{
			return l.rect == r.rect;
		}
		friend bool operator!=(const node& l, const node& r)
		{
			return !(l == r);
		}

		value_type rect;
		node* parent;
		node* left;
		node* right;
	};
public:
	class iterator {
		friend class bsp_tree;
		iterator(node& ref)
			: ref(&ref) {}
	public:
		const_reference operator*() const { return ref->rect; }

		friend bool operator== (const iterator& l, const iterator& r)
		{
			return l.ref == r.ref;
		}
		friend bool operator!= (const iterator& l, const iterator& r)
		{
			return !(l==r);
		}
	private:
		node* ref;
	};

	bsp_tree(const dim_type dim)
		: head(value_type(point_type(0,0),dim), 0)
	{}

	iterator insert(const dim_type dim)
	{
		return insert_recursive(dim, head);
	}

	void erase(iterator it)
	{
		delete it.ref;
	}

	iterator find(const value_type& t)
	{
		return find_recursive(t, head);
	}

	iterator end() { return iterator(head); }
private:
	node head;

	iterator insert_recursive(const dim_type dim, node& n)
	{
		if(dim > n.rect)
			return end();

		// case 1: left and right are absent
		if(!n.left && !n.right)
			return insert_node(n, n.left, value_type(point_type(n.rect.left, n.rect.top), dim));
		
		// case 2: right node is absent but left node is there
		if(!n.right)
			return insert_case_2(dim, n, *n.left, n.right);

		// case 2: symmetric case (left node is absent but right node is there)
		if(!n.left)
			return insert_case_2(dim, n, *n.right, n.left);

		// case 3: both nodes are there
		iterator ret = insert_recursive(dim, *n.left);
		if(ret == end())
			ret = insert_recursive(dim, *n.right);
		return ret;
	}

	iterator insert_case_2(const dim_type dim, node& ref, node& exist, node*& empty)
	{
		// first look if we can put the new rect in somewhere down the existing node
		iterator ret = insert_recursive(dim, exist);
		if(ret != end())
			return ret;
	
		// try to insert the node at the right side
		if(dim.w <= width(ref.rect) - width(exist.rect))
			if(dim.h <= height(ref.rect) - height(exist.rect))
				return insert_node(ref, empty, value_type(point_type(exist.rect.right + 1, 0), dim));

		// try to insert the node at the bottom side
		if(dim.h <= height(ref.rect) - height(exist.rect))
			if(dim.w <= width(ref.rect) - width(exist.rect))
				return insert_node(ref, empty, value_type(point_type(0, exist.rect.bottom + 1), dim));

		return end();
	}

	iterator insert_node(node& ref, node*& n, const value_type& rect)
	{
		n = new node(rect, &ref);
		return iterator(*n);
	}

	iterator find_recursive(const value_type& t, node& n)
	{
		if(n.rect == t)
			return n;
		if(n.left && contains(n.left->rect, t))
			return find_recursive(t, *n.left);
		if(n.right && contains(n.right->rect, t))
			return find_recursive(t, *n.right);
		return end();
	}
};

}

#endif
