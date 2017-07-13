template<class Type>
int BinarySearch7(Type a[], const Type& x, int n)
{
    if(n>0 && x>=a[0])
    {
        int left=0;
        int right=n-1;
        while (left < right)
        {
            int middle = (left+right+1)/2;
            if (x < a[middle]) right = middle;
            else left = middle;
        }
        if (x == a[left]) return left;
    }
    return -1;
}
