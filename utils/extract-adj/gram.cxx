
#encoding "utf-8"
#GRAMMAR_ROOT All

Attr -> Adj "типа" ;
All -> Adj interp (Ent.Attr) Noun<kwtype="орган"> interp (Ent.Name) ;
All -> Noun<kwtype="орган"> interp (Ent.Name) Attr interp (Ent.Attr)  ;
