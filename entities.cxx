#encoding "utf-8"
#GRAMMAR_ROOT All

//Entity -> Adj<gnc-agr[1]>* Noun<gnc-agr[1], gram='S', rt> ;
//SuperEntity -> Entity Word<kwtype="включение"> Entity;
//Fraza ->  Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1]>

//Объявление сущностей
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1], gram=~"род">;
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="допслова",gnc-agr[1], gram="A">* Word<kwtype="сущ", rt, gnc-agr[1], gram=~"род">;

Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="сущ", gn-agr[1], rt> Word<kwtype="сущ",gn-agr[1],gram="род">;
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="сущ", rt> Word<kwtype="прил",gnc-agr[2]>* Word<kwtype="сущ", gnc-agr[2], gram="род">;

Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="допслова", rt, gnc-agr[1],gram="S">;
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="допслова",gram="S,им", rt> Word<kwtype="прил",gnc-agr[2]>* Word<kwtype="сущ", gnc-agr[2], gram="род"> ('и') (Word<kwset=["сущ","допслова"], gnc-agr[2], gram="род">);
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Word<kwtype="сущ", rt> Word<kwtype="допслова", gnc-agr[2], gram="A">* Word<kwtype="сущ", gnc-agr[2], gram="род">;

//Включение допольнителньых прилагательных (замедляет скорость работы, но конкретизирует сущности)
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Adj<gnc-agr[1]>* Word<kwtype="сущ", gnc-agr[1], rt>;
Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Adj<gnc-agr[1]>* Word<kwtype="допслова",gram="S,им", rt, gnc-agr[1]> Word<kwtype="прил",gnc-agr[2]>* (Word<kwtype="сущ", gnc-agr[2], gram="род">) ('и') (Word<kwset=["сущ","допслова"], gnc-agr[2], gram="род">);

//Исключение лишних слов
NormEnt -> Ent<wfm=~"[а-я|А-Я]{1}",gram=~"PR">;

//Перевод с латинского  (Работает)
lat -> LBracket AnyWord* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
Grec -> lat AnyWord* interp(+Translate.grec) RBracket;
//Translate -> Ent interp(Translate.ru) Grec;
Translate -> Word interp(Translate.ru) Grec;

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


//Слова включения (Работает, добавить слова в статью и немного дораборать)

//mus -> (NormEnt<gram="вин"> interp (Including.item5)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item4)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item3)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item2)) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//Если выйдет необходимость выделять каждый факт по отдельности
//mus ->  NormEnt<gram="вин"> interp (Including.item5) (',') ('и') NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item1);
//Including -> NormEnt interp(Including.list) Word<kwtype="включение"> mus;
list -> (NormEnt<gram="вин">) (',') ('и') (NormEnt<gram="вин">) (',') ('и') (NormEnt<gram="вин">) (',') ('и') (NormEnt<gram="вин">) (',') ('и') NormEnt<gram="вин">;
Including ->  NormEnt interp(Including.list) (info) Word<kwtype="включение",gram="V"> list interp(Including.value);

//Связь плюс
Plus -> NormEnt "вместе" "с" NormEnt "составлять" NormEnt;
prim -> Plus interp (Example.state);

//Примеры
//primer -> NormEnt<gram="твор"> NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
primer -> (NormEnt) NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
prim -> primer interp (Example.state) list interp (Example.state);
//Word<kwtype="включение",gram="V"> list interp(Example.value);


//Работа с тире (доделать)  
//Including -> NormEnt interp(Including.Name1) '-' NormEnt interp(Including.Name2);

//Связь соединения.
Connection -> ('С') Word<gram="твор"> interp(Connection.first) Word<gram="им"> interp(Connection.second) Word<kwtype="включение"> ('при помощи') Word<gram="род"> interp (Connection.with);


//Вывод
//Final -> NormEnt interp(Entity.Name);

//Final -> list;
Final -> Translate;
Final -> Including;
Final -> prim;
//Final -> Connection;
Final -> Oborot;
Final -> Sinonim;

All -> Final;