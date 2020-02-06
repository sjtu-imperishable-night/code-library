int getmin( char s[] )
{
    int i , j , k , m , t ;
    m = strlen( s ) ;
    i = 0 ; j = 1 ; k = 0 ;
    while( i < m && j < m && k < m )
    {
        t = s[( i + k ) % m] - s[( j + k ) % m] ;
        if( !t )
            ++ k ;
        else
        {
            if( t > 0 )
                i += k + 1 ;
            else
                j += k + 1 ;
            if( i == j )
                j ++ ;
            k = 0 ;
        }

    }
    return min(i,j);
}
