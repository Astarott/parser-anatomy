#encoding "utf-8"
#GRAMMAR_ROOT All

//Entity -> Adj<gnc-agr[1]>* Noun<gnc-agr[1], gram='S', rt> ;
//SuperEntity -> Entity Word<kwtype="включение"> Entity;
//Fraza ->  Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1]>

//Прилагательные
ExtendAdj -> Word<kwset=["прил","допслова"],gnc-agr[1], GU=["A",~"partcp"]> ("и") (Word<kwset=["прил","допслова"],gnc-agr[1], GU=["A",~"partcp"]>*);
//Числительные
chislit -> Word<gram="NUM">;
chislit -> Word<wfm="[0-9]{1,10}">;
chislit -> Word<wfm="[I|L|V|X]{1,10}">;

//Объявление сущностей
Ent -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwtype="сущ", rt, gnc-agr[1], gram=~"род">;

//Конструкции с родительным падежом (типа "кость правого ребра").
Ent -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwset=["сущ","допслова"], gnc-agr[1], GU=["S"], rt> (ExtendAdj<gnc-agr[2], gram="род">) Word<kwset=["сущ","допслова"], gnc-agr[2], GU=["S","род"]> ('и') (ExtendAdj<gnc-agr[2], gram="род">) (Word<kwset=["сущ","допслова"], gnc-agr[2], GU=["S","род"]>);

//Дополнительные существительные
Ent -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwtype="допслова", rt, gnc-agr[1], GU=["S",~"род"]>;

//Включение допольнителньых прилагательных (замедляет скорость работы, но конкретизирует сущности)
Ent -> (chislit*) Adj<gnc-agr[1], GU=["A",~"partcp"]>* ('и') (Adj<gnc-agr[1], GU=["A"]>*) Word<kwtype="сущ", gnc-agr[1], rt>;
//Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Adj<gnc-agr[1]>* Word<kwtype="допслова",gram="S,им", rt, gnc-agr[1]> Word<kwtype="прил",gnc-agr[2]>* (Word<kwtype="сущ", gnc-agr[2], gram="род">) ('и') (Word<kwset=["сущ","допслова"], gnc-agr[2], gram="род">);

//В частных случаях сущности представляют собой одни прилагательные.
//Ent -> (chislit*) ExtendAdj;

//Исключение лишних слов
NormEnt -> Ent<wfm=~"[а-я|А-Я]{1}",gram=~"PR">;

//Перевод с латинского  (Работает)
lat -> LBracket AnyWord<~lat>* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
//lat -> LBracket AnyWord* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
Grec -> lat AnyWord<wfm=~"[)]{1}"* interp(+Translate.grec) RBracket;
//Translate -> Ent interp(Translate.ru) Grec;
Translate -> NormEnt interp(Translate.ru) Grec;

//Уточнения, синонимы и все остальное, что есть в скобках. (Работает)
info -> LBracket AnyWord<wfm=~"[)]{1}",~lat>+ interp(Sin.ent2 ::not_norm) RBracket;
Sinonim -> NormEnt interp(Sin.ent1 ::not_norm) info (Ent interp(+Sin.ent1 ::not_norm));


//Причастный и деепричастный оборот (Работает)
Part ->  Word<wfm=~"[,|(]{1}",~fw>* Participle<GU=["A,S"]> AnyWord<wfm=~"[.|,|)]{1}">*; 
Part2 ->  Word<wfm=~"[,]{1}",~fw>* ('к') 'который' (NormEnt) AnyWord<wfm=~"[.|,]{1}">*;
PartExtend -> Part;
PartExtend -> Part2;
//Oborot -> Part interp (Participle.ent); 
Oborot -> NormEnt interp(Participle.ent ::not_norm) Comma PartExtend interp (Participle.dop ::not_norm);
Oborot -> Part interp (Participle.dop ::not_norm) NormEnt interp(Participle.ent ::not_norm);

//Однородные члены.
//odnor -> NormEnt<gram="им"> (',') ('и') (NormEnt<gram="им">) (',') ('и') ('а также') (NormEnt<gram="им">) (',') ('и') ('а также') (NormEnt<gram="им">);
//list ->  NormEnt<gram="вин"> (',') ('и') (NormEnt<gram="вин">) (',') ('и') ('а также') (NormEnt<gram="вин">) (',') ('и') ('а также') (NormEnt<gram="вин">);

ou -> (',') ('и') ('а') (':') ('также') (Word<gram="SPRO">) NormEnt;
list -> NormEnt (ou) (ou) (ou) (ou) (ou);

//doplist -> list (NormEnt);

//Слова включения (Работает, добавить слова в статью и немного дораборать)

//mus -> (NormEnt<gram="вин"> interp (Including.item5)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item4)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item3)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item2)) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//Если выйдет необходимость выделять каждый факт по отдельности
//mus ->  NormEnt<gram="вин"> interp (Including.item5) (',') ('и') NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item1);
//Including -> NormEnt interp(Including.list) Word<kwtype="включение"> mus;

//Including ->  NormEnt interp(Including.list) (info) Word<kwtype="включение",gram="V"> list interp(Including.value);
Including -> Word<kwtype="вместимость"> list interp (Including.list) Word<kwtype="включение"> list interp (Including.value);
Including -> Word<kwtype="вместимость"> list interp (Including.list) Word<kwtype="включение"> list interp (Including.value);


//Связь соединения.
Connection -> ('С') NormEnt<gram="твор"> interp(Connection.first) NormEnt<gram="им"> interp(Connection.second) Word<kwtype="включение"> ('при помощи') Word<gram="род"> interp (Connection.with);
Connection -> NormEnt interp(Connection.first) "вместе" "с" NormEnt interp (Connection.with) Word<kwtype="равенство"> NormEnt interp(Connection.second);


//Связь равенства. Выглядит вполне неплохо, но нужно еще добавить разных случаев.

//sum -> NormEnt<gram="твор"> NormEnt<gram="род"> ('и') (",") (NormEnt<gram="род">)  ('и') (",") (NormEnt<gram="род">); 
//eq -> odnor interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2 ::not_norm); 
//eq -> sum interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2 ::not_norm); 
//eq -> NormEnt interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2:: not_norm);
eq -> list interp (Equality.Name1 ::not_norm) Word<kwtype="между"> list interp (Equality.option ::not_norm) (info) Word<kwtype="равенство"> list interp (Equality.Name2:: not_norm);
eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> list interp (Equality.Name2:: not_norm) Word<kwtype="между"> list interp (Equality.option ::not_norm);
eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство",gram="V"> list interp (Equality.Name2:: not_norm);
eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство",gram="V"> list interp (Equality.Name2:: not_norm);


//Примеры
//primer -> NormEnt<gram="твор"> NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
primer -> (NormEnt) NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
prim -> primer interp (Example.state) list interp (Example.state);
//Word<kwtype="включение",gram="V"> list interp(Example.value);


//Работа с тире (доделать)  
//Including -> NormEnt interp(Including.Name1) '-' NormEnt interp(Including.Name2);

//Вывод.
//Final -> NormEnt interp(Entity.Name);
//Final -> ExtendAdj interp(Entity.Name);

//Final -> sum;
//Final -> list;

Final -> Including;
Final -> eq;
Final -> Connection;

Final -> Translate;
//Final -> Oborot;
//Final -> Sinonim;

All -> Final;