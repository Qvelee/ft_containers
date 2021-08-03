/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/03 19:09:47 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/03 20:06:06 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{

template<typename T, typename Container = ft::vector<T> >
class stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

		explicit	stack(const container_type &container = container_type());
		~stack();

		bool				empty() const;
		size_type			size() const;
		value_type			&top();
		const value_type	&top() const;
		void				push(const value_type &value);
		void				pop();
	protected:
		container_type	c;
	private:
		template<typename T1, typename C>
		friend bool
		operator==(const stack<T1, C> &, const stack<T1, C> &);
		template<typename T1, typename C>
		friend bool
		operator!=(const stack<T1, C> &, const stack<T1, C> &);
		
		template<typename T1, typename C>
		friend bool
		operator<(const stack<T1, C> &, const stack<T1, C> &);
		
		template<typename T1, typename C>
		friend bool
		operator<=(const stack<T1, C> &, const stack<T1, C> &);
		
		template<typename T1, typename C>
		friend bool
		operator>(const stack<T1, C> &, const stack<T1, C> &);
		
		template<typename T1, typename C>
		friend bool
		operator>=(const stack<T1, C> &, const stack<T1, C> &);
};

template<typename T, typename Container>
stack<T, Container>::
stack(const container_type &container)
{
	c = container;
}

template<typename T, typename Container>
stack<T, Container>::
~stack() { }

template<typename T, typename Container>
bool	stack<T, Container>::
empty() const
{
	return c.empty();
}

template<typename T, typename Container>
typename stack<T, Container>::size_type		stack<T, Container>::
size() const
{
	return c.size();
}

template<typename T, typename Container>
typename stack<T, Container>::value_type	&stack<T, Container>::
top()
{
	return c.back();
}

template<typename T, typename Container>
const typename stack<T, Container>::value_type	&stack<T, Container>::
top() const
{
	return c.back();
}

template<typename T, typename Container>
void	stack<T, Container>::
push(const value_type &value)
{
	c.push_back(value);
}

template<typename T, typename Container>
void	stack<T, Container>::
pop()
{
	c.pop_back();
}

template <typename T, typename Container>
bool	operator==(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c == rigth.c;
}

template <typename T, typename Container>
bool	operator!=(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c != rigth.c;
}

template <typename T, typename Container>
bool	operator<(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c < rigth.c;
}

template <typename T, typename Container>
bool	operator<=(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c <= rigth.c;
}

template <typename T, typename Container>
bool	operator>(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c > rigth.c;
}

template <typename T, typename Container>
bool	operator>=(const stack<T, Container> &left, const stack<T, Container> &rigth)
{
	return left.c >= rigth.c;
}

} // namespace ft

#endif
