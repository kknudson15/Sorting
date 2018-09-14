/* 
Kyle Knudson
CSCI 591
cs301188
Project 10
due: 4/10/18
This file consists of the client program that generates an array of values depending on the users input.  The 
user enters in a value between 1 and 5000 to indicate the number of values that they wish to have in the array.  
After this prompt a second prompt appears, asking the user for a seed value so that the random number generator 
can populate the array.  Once the array is done, an insertion sort, quick sort and merge sort is performed, counting the steps in the algorithm 
along the way.  Once these sorts are complete a summary of the steps in the algorithm is displayed to the user.  
*/

#include <cstdlib>
#include <iostream>
using namespace std;

void insertion_sort(int A[],int number_of_items, int & insertion_count);
void merge_sort(int B[], int low, int high,int number_of_items, int & merge_count);
void merge(int B[],int low,int mid, int high,int number_of_items, int & merge_count);
void quick_sort(int C[],int low,int high, int & quick_count);
void partition ( int C[], int low, int high, int &m, int &n, int & quick_count );
void swap(int* a, int* b);

int main()
{
        int num_of_items;
        int seed;
        char answer1;
        char answer2;
		int merge_count = 0;
		int insertion_count = 0;
		int quick_count = 0;

        cout<<"Enter the number of values to generate and sort, between 1 and 5000: ";
        cin>>num_of_items;

        cout<<"Enter an integer seed value: ";
        cin>>seed;

        int merge[num_of_items];
        int insertion[num_of_items];
        int quick[num_of_items];

        srand(seed);
        for(int i=0;i<num_of_items;i++)
        {
                insertion[i] = (rand()%5000)+1;
                merge[i]     = insertion[i];
                quick[i]     = insertion[i];
        }

        cout<<"Print the values?(y/n): ";
        cin>>answer1;
        cout<<endl;


        if(answer1=='y')
        {
                cout<<"What sorting algorithm?(i for insertion sort || m for merge sort || q for quick sort: ";
                cin>>answer2;
                cout<<endl;

                cout<<"Unsorted: "<<endl;
                for(int i=0;i<num_of_items;i++)
                        cout<<quick[i]<<endl;
                cout<<"----------------------------------------"<<endl<<endl;
                cout<<"Sorted: "<<endl;
                insertion_sort(insertion,num_of_items, insertion_count);
                merge_sort(merge,0,num_of_items-1,num_of_items, merge_count);
                quick_sort(quick,0,num_of_items-1, quick_count);
                if(answer2=='i')
                {
                        for(int i=0;i<num_of_items;i++)
                                cout<<insertion[i]<<endl;
                }
                else if(answer2=='m')
                {
                        for(int i=0;i<num_of_items;i++)
                                cout<<merge[i]<<endl;
                }
                else//quick sort;
                {
                        for(int i=0;i<num_of_items;i++)
                                cout<<quick[i]<<endl;
                }

        }
        else
        {
                insertion_sort(insertion,num_of_items, insertion_count);
                merge_sort(merge,0,num_of_items-1,num_of_items, merge_count);
                quick_sort(quick,0,num_of_items-1, quick_count);
        }
cout<<"Insertion sort count: "<<insertion_count<<endl;
cout<<"Merge sort count: "<<merge_count<<endl;
cout<<"Quick sort count: "<<quick_count<<endl;
}


//preconditions: an array of integers is passed to the function, an integer that contains the 
// number of items in the array and an integer that is passed by reference that acts as the step counter for the sort
//postcondition: the array is sorted and the step counter is maintained back to the main since it was passed by reference.
void insertion_sort (int A[], int number_of_items, int & insertion_count)
{
        int j;
        for (int i=1; i<number_of_items; ++i)
        {

                j = i;
                while (j>0 && A[j] < A[j-1])
                {
                        insertion_count++;
                        swap(A[j],A[j-1]);
                        --j;
                }
        }
}

//preconditions: an array of integers is passed to the function,an integer that represents the low value, an integer that
// represents the high value in the array,  an integer that contains the number of items in the array and an integer that
// is passed by reference that acts as the step counter for the sort
//postcondition: the array is sorted and the step counter is maintained back to the main since it was passed by reference.
void merge_sort(int B[], int low, int high,int number_of_items, int & merge_count)
{
        int mid;
        if(low<high)
        {
                mid=(low+high)/2;
                merge_sort(B,low,mid,number_of_items, merge_count);
                merge_sort(B,mid+1,high,number_of_items, merge_count);
                merge(B,low,mid,high,number_of_items, merge_count);
        }
}

//preconditions: an array of integers is passed to the function,an integer that represents the low value,an integer that 
// represents the mid value in a section and an integer that represents the high value in the array,  an integer that contains
// the number of items in the array and an integer that is passed by reference that acts as the step counter for the sort.
//postconditions: merges the sections into a sorted array.
void merge(int B[],int low, int mid,int high,int number_of_items, int & merge_count)
{
        int D[number_of_items];
        int i1,i2,index;
        for(int i=low;i<=high;++i)
        {
        merge_count++;
        D[i]=B[i];
        }

        i1=low,
        i2=mid+1;
        index=low;

        while(i1<=mid && i2<=high)
        {
                merge_count++;
                if(D[i1]<D[i2])
                        {B[index++]=D[i1++];}
                else
                        {B[index++]=D[i2++];}
        }

        while(i1<=mid)
        {
                merge_count++;
                B[index++]=D[i1++];
        }

        while(i2<=high)
        {
                merge_count++;
                B[index++]=D[i2++];
        }
}

//preconditions: an array of integers is passed to the function,an integer that represents the low value, an integer that
// represents the high value in the array, an integer that is passed by reference that acts as the step counter for the sort
//postcondition: the array is sorted and the step counter is maintained back to the main since it was passed by reference.
void quick_sort (int C[], int low, int high, int & quick_count )
{
        int m, n;
        if ( low < high )
        {
                partition ( C, low, high, m, n, quick_count );
                quick_sort ( C, low, m, quick_count );
                quick_sort ( C, n, high, quick_count );
        }
}

//preconditions: an array of integers is passed to the function,an integer that represents the low value,an integer that 
// represents the mid value in a section and an integer that represents the high value in the array,
// an integer that is passed by reference that acts as marker for one section, an integer that is passed by reference that acts as another marker,
// and an integer that is passed by reference that acts as the step counter for the sort.
//Postconditions:  The array is shifted into the partitions that make the quick sort function.
void partition ( int C[], int low, int high, int &m, int &n, int & quick_count)
{
        int pivot = C[low];
        int lastS1 = low - 1;
        int firstU = low;
        int firstS3 = high + 1;

        while ( firstU < firstS3 )
        {
                quick_count++;
                if ( C[firstU] < pivot )        // S1
                {
                        ++lastS1;
                        swap ( C[firstU],C[lastS1] );
                        ++firstU;
                }
                else if ( C[firstU] == pivot ) // S2
                        {++firstU;}
                else // C[firstU] > pivot      // S3
                {
                        --firstS3;
                        swap ( C[firstU], C[firstS3] );
                }
        }
        m = lastS1;
        n = firstS3;
}

//preconditions:  two integer pointer variables are passed to the function
//postconditions: The values that are pointed to by the pointers, swap address locations.
void swap(int* a, int* b)
{
        int temp = *a;
        *a = *b;
        *b = temp;
}