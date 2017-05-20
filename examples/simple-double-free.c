void free(char *ptr)
  /**
    requires ptr->Char*(_)
    ensures emp;
  */

int main()
{
  /** emp */ 
  char *str = (char *) malloc(sizeof(char));
  /** str->Char*(_) */
  *str = 'a';
  /** str->Char*('a') */ 
  free(str);
  /** emp */ 
  free(str);
  // ERROR: Precondition of free is not satisfied.
  return(0);
}