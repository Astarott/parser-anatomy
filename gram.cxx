
#encoding "utf-8"
#GRAMMAR_ROOT All

Ent -> 'свод' 'череп' ;

Ent -> Adj<gnc-agr[1]>+ Noun<gnc-agr[1], rt> ;
Ent -> Noun<gnc-agr[1]> Adj<gnc-agr[1]>+ ;
Ent -> Noun ;

Ent -> Noun Ent+ ;

Rel -> Ent interp (Equality.Name1) "являться" Ent interp (Equality.Name2) ;
Rel -> Ent interp (Equality.Name1) "образовывать" Ent interp (Equality.Name2) ;
Rel -> Ent interp (Including.Name1) "содержать" Ent interp (Including.Name2) ;
Rel -> Ent interp (Including.Name1) "вдаваться" "между" Ent interp (Including.Name2) ;


All -> Rel; 

