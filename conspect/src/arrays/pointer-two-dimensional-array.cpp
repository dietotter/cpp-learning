int main()
{
    int **array = new int*[10]; // allocate an array of 10 int pointers — these are our rows
    for (int count = 0; count < 10; ++count)
    {
        array[count] = new int[5]; // these are our columns
    }

    // We can then access it as usual:
    array[9][4] = 3;

    // With this method, because each array column is dynamically allocated independently,
    // it's possible to make dynamically allocated two dimensional arrays, that are not rectangular
    // E.g., triangle-shaped array:
    int **triangleArray = new int*[10];
    for (int count = 0; count < 10; ++count)
    {
        triangleArray[count] = new int[count+1];
    }

    // Dynamically deallocating requires a loop as well:
    for (int count = 0; count < 10; ++count)
    {    
        delete[] array[count];
        delete[] triangleArray[count];
    }
    delete[] array; // this needs to be done last
    delete[] triangleArray; // this needs to be done last

    // Because allocating/deallocating two-dim arrays is complex and easy to mess up,
    // it's often easier to flatten a two-dim array (of size x by y) into a one-dim array of size x * y:
    int *flattenedArray = new int[50];
    
    // simple math can be used to convert a row and column index for a rectangulat two-dim array
    // into a single index for a one-dim array:
    int row{ 9 };
    int col{ 4 };
    int numberOfColumns{ 5 };
    flattenedArray[(row * numberOfColumns) + col] = 3;

    return 0;
}