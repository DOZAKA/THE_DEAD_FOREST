//
//  PriorityQueue.hpp
//  TheDeadForest
//
//  Created by 남준현 on 2015. 11. 24..
//
//

#pragma once

#include <vector>
#include <exception>

namespace realtrick
{
    
    template <class T>
    class PriorityQ
    {
        
    public:
        
        PriorityQ(int maxSize) : _maxSize(maxSize), _size(0)
        {
            _heap.assign(maxSize + 1, T());
        }
        
        bool empty() const { return (_size == 0); }
        
        void insert(const T item)
        {
            if(_size + 1 > _maxSize)
            {
                throw std::runtime_error("<PriorityQ::insert> Heap size is excessed.");
            }
            
            ++_size;
            _heap[_size] = item;
            _reorderUpwards(_size);
        }
        
        T pop()
        {
            std::swap(_heap[1], _heap[_size]);
            _reorderDownwards(1);
            return _heap[_size--];
        }
        
        const T& peek() const { return _heap[1]; }
        
    private:
        
        std::vector<T>          _heap;
        int                     _size;
        int                     _maxSize;
        
    private:
        
        void _reorderUpwards(int nd)
        {
            while ( nd > 1 && _heap[nd / 2] < _heap[nd] )
            {
                std::swap(_heap[nd / 2], _heap[nd]);
                nd /= 2;
            }
        }
        
        void _reorderDownwards(int nd)
        {
            int heapSize = _size - 1;
            
            while( 2 * nd <= heapSize)
            {
                int child = 2 * nd;
                
                if( child < heapSize && _heap[child] < _heap[child + 1] )
                {
                    ++child;
                }
                
                if(_heap[nd] < _heap[child])
                {
                    std::swap(_heap[child], _heap[nd]);
                    nd = child;
                }
                else
                {
                    break;
                }
            }
        }
        
    };
    
    
    template <class T>
    class PriorityQLow
    {
        
    public:
        
        PriorityQLow(int maxSize) : _maxSize(maxSize), _size(0)
        {
            _heap.assign(maxSize + 1, T());
        }
        
        bool empty() const { return (_size == 0); }
        
        void insert(const T item)
        {
            if( _size + 1 > _maxSize )
            {
                throw std::runtime_error("<PriorityQLow::insert> Heap size is excessed.");
            }
            
            ++_size;
            _heap[_size] = item;
            _reorderUpwards(_size);
        }
        
        T pop()
        {
            std::swap(_heap[1], _heap[_size]);
            _reorderDownwards(1);
            return _heap[_size--];
        }
        
        const T& peek() const { return _heap[1]; }
        
    private:
        
        std::vector<T>          _heap;
        int                     _size;
        int                     _maxSize;
        
    private:
        
        void _reorderUpwards(int nd)
        {
            while ( nd > 1 && _heap[nd / 2] > _heap[nd] )
            {
                std::swap(_heap[nd / 2], _heap[nd]);
                nd /= 2;
            }
        }
        
        void _reorderDownwards(int nd)
        {
            int heapSize = _size - 1;
            
            while ( nd * 2 <= heapSize )
            {
                int child = nd * 2;
                
                if( child < heapSize && _heap[child] > _heap[child + 1] )
                {
                    ++child;
                }
                
                if( _heap[nd] > _heap[child] )
                {
                    std::swap(_heap[nd], _heap[child]);
                    nd = child;
                }
                else
                {
                    break;
                }
            }
        }
        
    };
    
    
    template <class keyType>
    class IndexedPriorityQLow
    {
      
    public:
        
        IndexedPriorityQLow(std::vector<keyType>& keys, int maxSize) :
        _vecKeys(keys), _maxSize(maxSize), _size(0)
        {
            _heap.assign(maxSize + 1, 0);
            _invHeap.assign(maxSize + 1, 0);
        }
        
        
        bool empty() const { return (_size == 0); }
        
        void insert(const int idx)
        {
            if(_size + 1 > _maxSize)
            {
                throw std::runtime_error("<IndexedPriorityQLow::insert> Heap size is excessed.");
            }
            
            ++_size;
            
            _heap[_size] = idx;
            _invHeap[idx] = _size;
            _reorderUpwards(_size);
        }
        
        int pop()
        {
            _swap(1, _size);
            _reorderDownwards(1);
            return _heap[_size--];
        }
        
        void changePriority(const int idx)
        {
            _reorderUpwards(_invHeap[idx]);
        }
        
    private:
        
        std::vector<keyType>&           _vecKeys;
        std::vector<int>                _heap;
        std::vector<int>                _invHeap;
        
        int                             _size;
        int                             _maxSize;
        
    private:
        
        void _swap(int a, int b)
        {
            std::swap(_heap[a], _heap[b]);
            _invHeap[_heap[a]] = a;
            _invHeap[_heap[b]] = b;
        }
        
        void _reorderUpwards(int nd)
        {
            while ( nd > 1 && _vecKeys[_heap[nd / 2]] > _vecKeys[_heap[nd]] )
            {
                _swap(nd / 2, nd);
                nd /= 2;
            }
        }
        
        void _reorderDownwards(int nd)
        {
            int heapSize = _size - 1;
            
            while( nd * 2 <= heapSize )
            {
                int child = nd * 2;
                
                if(child < heapSize && _vecKeys[_heap[child]] > _vecKeys[_heap[child + 1]])
                {
                    ++child;
                }
                
                if(_vecKeys[_heap[nd]] > _vecKeys[_heap[child]])
                {
                    _swap(child, nd);
                    nd = child;
                }
                else
                {
                    break;
                }
            }
        }
        
    };
    
}


















