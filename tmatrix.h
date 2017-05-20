#ifndef _TMATRIX_H_
#define _TMATRIX_H_

#include <iostream>

using namespace std;
enum {DIFFERENT_SIZES, BAD_SIZE, BAD_POS};

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // ������ �������
  int StartIndex; // ������ ������� �������� �������
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // ����������� �����������
  ~TVector();
  int GetSize()      { return Size;       } // ������ �������
  int GetStartIndex(){ return StartIndex; } // ������ ������� ��������
  ValType& operator[](int pos); // ������
  bool operator==(const TVector &v) const;  // ���������
  bool operator!=(const TVector &v) const;  // ���������
  TVector& operator=(const TVector &v);     // ������������

  // ��������� ��������
  TVector  operator+(const ValType &val);   // ��������� ������
  TVector  operator-(const ValType &val);   // ������� ������
  TVector  operator*(const ValType &val);   // �������� �� ������

  // ��������� ��������
  TVector  operator+(const TVector &v);     // ��������
  TVector  operator-(const TVector &v);     // ���������
  ValType  operator*(const TVector &v);     // ��������� ������������

  // ����-�����
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < (v.Size-v.StartIndex); i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
    for (int i = 0; i < (v.Size-v.StartIndex); i++)
      out << v.pVector[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	Size = s;
	StartIndex = si;
	pVector = new ValType [Size - StartIndex];
	for (int i = 0; i < Size - StartIndex; i++)
     pVector[i] = 0;
} 

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType [Size - StartIndex];
	for (int i = 0; i < Size - StartIndex; i++)
		pVector[i] = v.pVector[i];

} 

template <class ValType>
TVector<ValType>::~TVector()
{
	delete [] pVector;
}

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos)
{
	if (pos < StartIndex || pos >= Size)
		throw BAD_POS;
	return pVector [pos - StartIndex];
} 

template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (Size != v.Size || StartIndex != v.StartIndex)
		return 0;
	for (int i = 0; i < Size - StartIndex; i++)
		if (pVector[i] != v.pVector[i])
			return 0;
	return 1;
	
} 

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !( *this == v );
} 

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{
	delete [] pVector;
 	Size = v.Size;
 	StartIndex = v.StartIndex;
 	pVector = new ValType [Size - StartIndex];
	for (int i = 0; i < (Size - StartIndex); i++)
		pVector[i] = v.pVector[i];
	return *this;
} 

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector <ValType> res (Size, 0);
	for (int i = 0; i < StartIndex; i++)
		res[i] = val;
	for (int j = 0; j < Size - StartIndex; j++)
		res[StartIndex + j] = pVector[j] + val;
	return res;

} 

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector <ValType> res (Size, 0);
	for (int i = 0; i < StartIndex; i++)
		res[i] = -val;
	for (int j = 0; j < Size - StartIndex; j++)
		res[StartIndex + j] = pVector[j] - val;
	return res;
} 
	

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector <ValType> res (Size, StartIndex);
	for (int i = 0; i < Size - StartIndex; i++)
		res[StartIndex + i] = pVector[i] * val;
		return res;

} 

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw DIFFERENT_SIZES;
	
	if (StartIndex <= v.StartIndex)
	{
		TVector <ValType> res (Size, StartIndex);
		for (int i = 0; i < Size - StartIndex; i++)
			res.pVector[i] = pVector [i];
		for (int j = 0; j < Size - v.StartIndex ; j++)
			res.pVector[v.StartIndex - StartIndex + j] = res.pVector[v.StartIndex - StartIndex + j] + v.pVector[j];
		return res;
	}
	TVector <ValType> res (Size, v.StartIndex);
		for (int i = 0; i < Size - v.StartIndex; i++)
			res.pVector[i] = v.pVector [i];
		for (int j = 0; j < Size - StartIndex ; j++)
			res.pVector[StartIndex - v.StartIndex + j] = res.pVector[StartIndex - v.StartIndex + j] + pVector[j];
		return res;

} 

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size)
		throw DIFFERENT_SIZES;
	
	if (StartIndex <= v.StartIndex)
	{
		TVector <ValType> res (Size, StartIndex);
		for (int i = 0; i < Size - StartIndex; i++)
			res.pVector[i] = pVector [i];
		for (int j = 0; j < Size - v.StartIndex ; j++)
			res.pVector[v.StartIndex - StartIndex + j] = res.pVector[v.StartIndex - StartIndex + j] - v.pVector[j];
		return res;
	}
	TVector <ValType> res (Size, v.StartIndex);
		for (int i = 0; i < Size - v.StartIndex; i++)
			res.pVector[i] = - v.pVector [i];
		for (int j = 0; j < Size - StartIndex ; j++)
			res.pVector[StartIndex - v.StartIndex + j] = res.pVector[StartIndex - v.StartIndex + j] + pVector[j];
		return res;

} 

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v)

{
	if (Size != v.Size)
		throw DIFFERENT_SIZES;
	ValType res = 0;
	if (StartIndex <= v.StartIndex)
	{
		for (int i = 0; i < Size - v.StartIndex; i++)
		res = res + (v.pVector[i]*pVector[v.StartIndex - StartIndex + i]);
		return res;
	}
	for (int i = 0; i < Size - StartIndex; i++)
		res = res + (pVector[i]*v.pVector[StartIndex - v.StartIndex + i]);
		return res;
}
		
	



// ����������������� �������
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // �����������
  TMatrix(const TVector<TVector<ValType> > &mt); // �������������� ����
  bool operator==(const TMatrix &mt) const;      // ���������
  bool operator!=(const TMatrix &mt) const;      // ���������
  TMatrix& operator= (const TMatrix &mt);        // ������������
  TMatrix  operator+ (const TMatrix &mt);        // ��������
  TMatrix  operator- (const TMatrix &mt);        // ���������
  TMatrix  operator* (TMatrix mt);        // ���������
  TMatrix  operator/ (TMatrix &mt);        // �������
  ValType Det (); // ������������
  TMatrix Reverse ();// �������� �������

  // ���� / �����
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	Size = s;
	for (int i=0; i<Size;i++)
	{
		pVector[i] = TVector <ValType> (Size, i);
		
	}

} 


template <class ValType> // ����������� �����������
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt) 
  {
	  Size = mt.Size;
	  for (int i=0; i<Size;i++)
	pVector[i] = mt.pVector[i];

  }



template <class ValType> // ����������� �������������� ����
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // ���������
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	if (Size != mt.Size)
		return 0;
	for (int i = 0; i < Size; i++)
		if (pVector[i] != mt.pVector[i])
			return 0;
	return 1;

} 

template <class ValType> // ���������
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return !( *this == mt );
} 

template <class ValType> // ������������
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	Size = mt.Size;
	delete [] pVector;
	pVector = new TVector<ValType>[Size];
	  for (int i=0; i<Size;i++)
	pVector[i] = mt.pVector[i];
	  
	  return * this;

} 

template <class ValType> // ��������
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
		throw DIFFERENT_SIZES;
	TMatrix <ValType> res (Size);
	for (int i=0; i<Size;i++)
		res.pVector [i] = pVector[i] + mt.pVector[i];
	return res;



} 

template <class ValType> // ���������
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	if (Size != mt.Size)
		throw DIFFERENT_SIZES;
	TMatrix <ValType> res (Size);
	for (int i=0; i<Size;i++)
		res.pVector [i] = pVector[i] - mt.pVector[i];
	return res;
} 



template <class ValType> // ������������
ValType TMatrix<ValType>::Det ()
{
	ValType det = 1;
	for (int i = 0; i < Size; i++)
	{
		det = det * ((*this)[i][i]);
		cout << ((*this)[i][i]) <<'\n';
	}
		
			
		
	
	return det;
}



template <class ValType> // ���������
TMatrix <ValType> TMatrix <ValType>::operator* (TMatrix<ValType> mt)
{

	if (Size != mt.Size)
		throw DIFFERENT_SIZES;
	TMatrix <ValType> res (Size);
	for (int i = 0; i < Size; i++)
	     for (int j = i; j < Size; j++)
			 for (int z = i; z < j + 1; z++)
			 {
				 res[i][j] += (*this)[i][z]  * mt[z][j];
				 
			 }
	
		
	return res;

	
}


template <class ValType> // �������
TMatrix <ValType> TMatrix <ValType>::operator/ (TMatrix<ValType> &mt)
{

	TMatrix <ValType> A (Size);
	TMatrix <ValType> res (Size);
	A = mt.Reverse();
	res = (*this) * A;


	
	
		
	return res;

	
}





template <class ValType> // �������� �������
TMatrix <ValType> TMatrix <ValType>::Reverse ()
{
	TMatrix <ValType> res, E;
	res.Size = Size;
	E = (*this);

	for (int i = 0; i < Size; i++)
	{
		res.pVector [i] = TVector <ValType> (Size, i);
		res[i][i] = 1;
	    for (int j = i; j < Size-1; j++)
		{
			res [i][j+1] = 0;
		}
	}


	for (int i = 0; i < Size; i++)
	{
		res.pVector[i] = res.pVector[i] * (1/(E[i][i]));
		E.pVector[i] = E.pVector[i] * (1/(E[i][i]));
		
		
	}
	
	for (int i = Size - 1; i > 0; i--)
		for (int j = i - 1; j >= 0; j--)
		{
			res.pVector[j] = res.pVector[j] + (res.pVector[i] * (-E[j][i]));
			E.pVector[j] = E.pVector[j] + (E.pVector[i] * (-E[j][i]));
			
			
		}
		

		

	return res;
}
		



// TVector �3 �2 �4 �6
// TMatrix �2 �2 �3 �3
#endif