#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <map>
#include <string>
#include <sstream>

namespace ullman {

	//efficient matrix
	template<typename T>
		class Matrix {
			public:
				Matrix<T>(size_t nrows, size_t ncolumn) :
					_m_nrows(nrows), _m_ncolumns(ncolumn), _m_change(true), 
					_m_value(nrows, std::vector<T>(ncolumn, 0)) {};

				Matrix<T>() : _m_nrows(0), _m_ncolumns(0), _m_change(true) {};

				inline Matrix<T> operator * (const Matrix<T>& other) const;

				inline Matrix<T> transposition() const;

				inline void set(size_t i, size_t j, T v);

				inline T get(size_t i, size_t j) const;

				inline void fill(T v);

				inline void fill(size_t row, T v);

				void resize(size_t size_i, size_t size_j);

				inline void clear();

				inline const char * c_str();

				//{nrows, ncolumns}
				std::pair<size_t, size_t> size() const
				{
					return std::make_pair(_m_nrows, _m_ncolumns);
				}

			private:
				size_t _m_ncolumns, _m_nrows;
				std::string _m_str;
				bool _m_change;
				std::vector<std::vector<T> > _m_value;
		};

	template <typename T>
		inline Matrix<T> Matrix<T>::transposition() const
		{
			Matrix<T> matrix(_m_ncolumns, _m_nrows);

			for (size_t i = 0; i < _m_nrows; ++i) {
				for (size_t j = 0; j < _m_ncolumns; ++j) {
					matrix.set(j, i, this->get(i, j));
				}
			}

			return matrix;
		}

	template <typename T>
		inline Matrix<T> Matrix<T>::operator * (const Matrix<T>& other) const
		{
			std::pair<size_t, size_t> other_size = other.size();

			if (other_size.first != _m_ncolumns)
				return Matrix<T>();

			Matrix<T> matrix(_m_nrows, other_size.second);
			for (size_t i = 0; i < _m_nrows; ++i) {
				for (size_t j = 0; j < other_size.second; ++j) {
					T tmp = 0;
					for (size_t k = 0; k < _m_ncolumns; ++k) {
						tmp += this->get(i, k) * other.get(k, j);
					}
					matrix.set(i, j, tmp);
				}
			}

			return matrix;
		}


	template <typename T>
		inline void Matrix<T>::set(size_t i, size_t j, T v)
		{
			if (i < _m_nrows && i >= 0 && j < _m_ncolumns && j >= 0) {
				_m_value[i][j] = v;
				_m_change = true;
			}
		}


	template <typename T>
		inline T Matrix<T>::get(size_t i, size_t j) const
		{
			if (i < _m_nrows && i >= 0 && j < _m_ncolumns && j >= 0) {
				return _m_value[i][j];
			}
			return 0;
		}

	template <typename T>
		inline void Matrix<T>::fill(T v)
		{
			for (size_t i = 0; i < _m_nrows; ++i) {
				_m_value[i].assign(_m_ncolumns, v);
			}
			_m_change = true;
		}

	template <typename T>
		inline void Matrix<T>::fill(size_t nrow, T v)
		{
			if (nrow < _m_nrows) {
				_m_value[nrow].assign(_m_ncolumns, v);
			}
		}

	template <typename T>
		void Matrix<T>::resize(size_t size_i, size_t size_j)
		{
			if (_m_value.size() < size_i) {
				_m_value.resize(size_i, std::vector<T>(_m_ncolumns, 0));
			}

			_m_nrows = size_i;

			if (_m_value[0].size() < size_j) {
				for (size_t i = 0; i < _m_nrows; ++i) {
					_m_value[i].resize(size_j, 0);
				}
			}

			_m_ncolumns = size_j;

			_m_change = true;
		}

	template <typename T>
		inline void Matrix<T>::clear()
		{
			for (size_t i = 0; i < _m_nrows; ++i) {
				_m_value[i].clear();
			}
			_m_ncolumns = 0;
			_m_nrows = 0;
			_m_change = true;
		}

	template <typename T>
		inline const char * Matrix<T>::c_str()
		{
			if (_m_change) {
				std::stringstream ss;
				for (size_t i = 0; i < _m_nrows; ++i) {
					for (size_t j = 0; j < _m_ncolumns; ++j) {
						ss << _m_value[i][j] << " ";
					}
					ss << "\n";
				}

				_m_str = ss.str();
			}

			_m_change = false;
			return _m_str.c_str();
		}
}//namespace ullman
#endif
