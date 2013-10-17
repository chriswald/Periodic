bool equals(char *one,char *two,int size)
{
    for (int i=0; i<size; i++)
    {
        if (one[i]!=two[i])
            return false;
    }

    return true;
}
