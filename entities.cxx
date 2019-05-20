#encoding "utf-8"
#GRAMMAR_ROOT All

//Entity -> Adj<gnc-agr[1]>* Noun<gnc-agr[1], gram='S', rt> ;
//SuperEntity -> Entity Word<kwtype="включение"> Entity;
//Fraza ->  Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1]>

//Прилагательные
//ExtendAdj -> Word<kwset=["прил","допслова"],gnc-agr[1], GU=~["partcp,S"]> ("и") (Word<kwset=["прил","допслова"],gnc-agr[1], GU=~["partcp,S"]>*);
ExtendAdj -> Word<kwset=["прил","допслова"],gnc-agr[1], gram=~"S,partcp,PR,APRO"> (info) ("и") (",") (Word<kwset=["прил","допслова"],gnc-agr[1], gram=~"S,partcp,PR,APRO">*) (info) ("и") (",") (Word<kwset=["прил","допслова"],gnc-agr[1], gram=~"S,partcp,PR,APRO">*);
ExtendAdj -> Adj<gnc-agr[1], gram=~"S,partcp,PR,APRO"> (info) ("и") (Adj<gnc-agr[1], gram=~"S,partcp,PR,APRO">*) (info) ("и") (Adj<gnc-agr[1], gram=~"S,partcp,PR,APRO">*);

//Числительные
chislit -> Word<gram="NUM">;
chislit -> Word<wfm="[0-9|,|%]{1,10}">;
chislit -> Word<wfm="[I|L|V|X]{1,10}">;

//Объявление сущностей
Ent -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwtype="сущ", rt, gnc-agr[1]>;

//Дополнительные существительные
Ent -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwtype="допслова", rt, gnc-agr[1], GU=["S"]>;

//Сущности, которые отделены запятой, например, пассивная и активная части. (существительное в мн. числе, а прил в ед.числе)
Ent -> (chislit*) (ExtendAdj<c-agr[1]>) Word<kwset=["сущ","допслова"], rt, c-agr[1], GU=["S"]>;
//Twoent -> temp<gc-agr[1]> interp (Entity.Name) ("и") temp<gc-agr[1]> Word<kwtype="сущ", rt, gc-agr[1], gram="мн"> interp (+Entity.Name);
//Twoent -> temp<gc-agr[1]> ("и") temp<gc-agr[1]> interp (Entity.Name) Word<kwtype="сущ", rt, gc-agr[1], gram="мн"> interp (+Entity.Name);
//Сущности, являющиеся единичными прилагательными.

adjent -> (chislit*) ExtendAdj;

//Конструкции с родительным падежом (типа "кость правого ребра").
SuperEnt -> (chislit*) (ExtendAdj<gnc-agr[1]>) Word<kwset=["сущ","допслова"], gnc-agr[1], GU=["S"], rt> (info) (chislit*) (ExtendAdj<gnc-agr[2], gram="род">) Word<kwset=["сущ","допслова"], gnc-agr[2], GU=["S","род"]> ('и') (Word<gram="SPRO">) (ExtendAdj<gnc-agr[3], gram="род">) (Word<kwset=["сущ","допслова"], gnc-agr[3], GU=["S","род",~"вин"]>);
//SuperEnt -> (ExtendAdj<gnc-agr[2], gram="род">) Word<kwset=["сущ","допслова"], gnc-agr[2], GU=["S","род"]> ('и') (Word<gram="SPRO">) (ExtendAdj<gnc-agr[2], gram="род">) (Word<kwset=["сущ","допслова"], gnc-agr[2], GU=["S","род",~"вин"]>);
//SuperEnt -> (ExtendAdj<gnc-agr[1], gram="род">) Word<kwset=["сущ","допслова"], gnc-agr[1], GU=["S","род"]>;

//Включение допольнителньых прилагательных (замедляет скорость работы, но конкретизирует сущности)
//Ent -> (chislit*) Adj<gnc-agr[1], gram=~"S,partcp,PR,APRO">* ('и') (Adj<gnc-agr[1], gram=~"S,partcp,PR,APRO">*) Word<kwtype="сущ", gnc-agr[1], rt>;
//Ent -> (Word<gram="NUM">*) (Word<wfm="[0-9]{1,10}">*) Adj<gnc-agr[1]>* Word<kwtype="допслова",gram="S,им", rt, gnc-agr[1]> Word<kwtype="прил",gnc-agr[2]>* (Word<kwtype="сущ", gnc-agr[2], gram="род">) ('и') (Word<kwset=["сущ","допслова"], gnc-agr[2], gram="род">);

//В частных случаях сущности представляют собой одни прилагательные.
//Ent -> (chislit*) ExtendAdj;

//Исключение лишних слов
//NormEnt -> Twoent<wfm=~"[а-я|А-Я]{1}",gram=~"PR">;
NormEnt -> Ent<wfm=~"[а-я|А-Я]{1}",gram=~"PR">;


//Уточнения, синонимы и все остальное, что есть в скобках. (Работает)
//info -> LBracket AnyWord<wfm=~"[)]{1}",~lat>+ interp(Sin.ent2 ::not_norm) RBracket;
info -> LBracket AnyWord<wfl=~"[)]{1}">+ interp (Sin.ent2 :: not_norm) RBracket;
Sinonim -> NormEnt interp(Sin.ent1 ::not_norm) info (NormEnt interp(+Sin.ent1 ::not_norm));
Sinonim -> ExtendAdj<gnc-agr[1]> interp(Sin.ent1 :: not_norm) info ("и") (ExtendAdj<gnc-agr[1]>) Word<kwset=["сущ","допслова"], gram="S", rt, gnc-agr[1]> interp(+Sin.ent1 :: not_norm);
Sinonim -> Word<kwset=["сущ","допслова"], gram="S", rt, gnc-agr[1]> interp(Sin.ent1 :: not_norm) ExtendAdj<gnc-agr[1]> interp(+Sin.ent1 :: not_norm) info;
//тут доделать. Два разных факта в одном предложении. 
//Sinonim -> Word<kwset=["прил","допслова"],gnc-agr[1], gram=~"S,partcp,PR,APRO"> Word<kwset=["прил","допслова"],gnc-agr[1], gram=~"S,partcp,PR,APRO">* interp(Sin.ent1 ::not_norm) Word<kwset=["сущ","допслова"],gram="S", rt, gnc-agr[1]> interp(+Sin.ent1 :: not_norm) (LBracket) (AnyWord<wfm=~"[)]{1}",~lat>+) (RBracket) "и" ExtendAdj<gnc-agr[1]> interp(+Sin.ent1 :: not_norm) info;


//Для конструкций, где уточнение стоит в именительном падеже.
//forSinonim -> NormEnt<gram="им"> AnyWord<wfm=~"[(]{1}",~lat>*;
//Sinonim -> forSinonim  info<gram="им">;


//Причастный и деепричастный оборот (Работает)
//AnyWord<wfm=~"[,|)]{1}">*; 
Part -> (Comma) ("(") AnyWord<wff=~"[,|(]{1}">* Word<gram="ger"> AnyWord<wfl=~"[,|)]{1}">* (Comma) (">") ;
Part -> (Comma) ("(") AnyWord<wff=~"[,|(]{1}">* Participle<GU=["partcp,~A"]> AnyWord<wfl=~"[,|)]{1}">* (Comma) (")"); 
//Part2 ->  Word<wfm=~"[,]{1}",~fw>* ('к') 'который' (NormEnt) AnyWord<wfm=~"[.|,]{1}">*;

//PartExtend -> Part interp(Participle.ent ::not_norm);
//PartExtend -> Part2;
//Oborot -> Part interp (Participle.ent); 
//Oborot -> NormEnt interp(Participle.ent ::not_norm) Comma PartExtend interp (Participle.dop ::not_norm);
//Oborot -> Part interp (Participle.dop ::not_norm) NormEnt interp(Participle.ent ::not_norm);

//Однородные члены и все, что с ними связано.
od -> (",") ("и") ("а") (":") ("также") ("или") ("как") ("между") (Word<gram="SPRO">) NormEnt;
odrod ->  (",") ("и") ("или") (Word<gram="SPRO">) SuperEnt;
pril -> (",") ("и") (info) (Word<gram="SPRO">) adjent;
advert -> (",") ("и") Word<gram="ADV">;
listadv -> Word<gram="ADV"> (advert) (advert) (advert);
list -> NormEnt (od) (od) (od) (od) (od);
listrod -> SuperEnt (odrod) (odrod);
listpril -> adjent (pril) (pril) (pril) (pril) (pril);
superlist -> list (",") ("и") listrod;
//Связь 2. Слова включения (Работает, добавить слова в статью и немного дораборать)

//mus -> (NormEnt<gram="вин"> interp (Including.item5)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item4)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item3)) (',') ('и') (NormEnt<gram="вин"> interp (Including.item2)) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//Если выйдет необходимость выделять каждый факт по отдельности
//mus ->  NormEnt<gram="вин"> interp (Including.item5) (',') ('и') NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item4) (',') ('и') NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item3) (',') ('и') NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item2) (',') ('и') NormEnt<gram="вин"> interp (Including.item1);
//mus ->  NormEnt<gram="вин"> interp (Including.item1);
dialist -> (diap) (info) (Adj) list;
diaplist -> (diap) (info) (Adj) superlist;
Including -> Word<kwtype="вместимость"> list interp (Including.list) Word<kwtype="включение"> ("из") dialist interp (Including.value :: not_norm);
Including -> Word<kwtype="вместимость"> SuperEnt interp (Including.list) Word<kwtype="включение"> ("из") dialist interp (Including.value :: not_norm);
Including -> list interp (Including.value) Word<kwtype="включение"> "в" "состав" SuperEnt interp (Including.list);
Including -> SuperEnt interp (Including.value) Word<kwtype="включение"> "в" "состав" SuperEnt interp (Including.list);

Including -> list interp (Including.list) (info) Word<kwtype="включение"> ("из") dialist interp (Including.value);
Including -> list interp (Including.list) (info) Word<kwtype="включение"> ("из") listrod interp (Including.value);

Including -> list interp (Including.list) (info) Word<kwtype="включение"> list interp (Including.value ::not_norm);
Including -> list interp (Including.list) (info) Word<kwtype="включение"> NormEnt interp (Including.value ::not_norm) (info) "и" interp (+Including.value) adjent interp (+Including.value ::not_norm) (info);
Including -> NormEnt interp (Including.list) Word<kwtype="часть"> ("на") dialist interp (Including.value);
Including -> NormEnt interp (Including.value) (info) Word<kwtype="включение"> ("также") Word<kwtype="вместимость"> ("своем") ("теле") SuperEnt interp(Including.list); 
Including -> NormEnt interp (Including.value) (info) Word<kwtype="включение"> ("также") Word<kwtype="вместимость"> ("своем") ("теле") NormEnt interp(Including.list); 
Including -> list interp (Including.list) Word<kwtype="включение"> NormEnt interp (Including.value);
Including -> list interp (Including.list) Word<kwtype="включение"> NormEnt interp (Including.value) info interp (+Including.value);
Including -> NormEnt interp (Including.list) Word<kwtype="включение"> listrod interp (Including.value);
Including -> Word<kwtype="включение"> NormEnt interp (Including.list ::not_norm) listpril interp (Including.value ::not_norm);
Including -> superlist interp (Including.value) Word<kwtype="включение"> Word<kwtype="вместимость"> SuperEnt interp (Including.list);
Including -> Word<kwtype="вместимость"> SuperEnt interp (Including.list) (info) Word<gram=~"V">* Word<kwtype="включение"> SuperEnt interp (Including.value) (info);

Including -> NormEnt interp (Including.list) Word<kwtype="включение"> Word<gram="SPRO"> NormEnt interp (Including.value) info interp (+Including.value) "—" SuperEnt Comma "или" NormEnt Comma "и" interp (+Including.value) NormEnt interp (+Including.value ::not_norm);
//Including -> SuperEnt interp (Including.list) Word<kwtype="включение"> list interp (Including.value);
//Including -> list interp (Including.value) Part Word<kwtype="включение"> NormEnt interp (Including.list);

Including -> NormEnt interp (Including.list) (info) Comma Word<kwtype="вместимость"> Word<kwtype="который"> (listadv) Word<kwtype="включение"> (listadv) NormEnt interp (Including.value); 
Including -> NormEnt interp (Including.list) (info) Comma Word<kwtype="вместимость"> Word<kwtype="который"> (listadv) Word<kwtype="включение"> (listadv) SuperEnt interp (Including.value); 
Including -> SuperEnt interp (Including.list) (info) Comma Word<kwtype="вместимость"> Word<kwtype="который"> (listadv) Word<kwtype="включение"> (listadv) NormEnt interp (Including.value); 
Including -> SuperEnt interp (Including.list) (info) Comma Word<kwtype="вместимость"> Word<kwtype="который"> (listadv) Word<kwtype="включение"> (listadv) SuperEnt interp (Including.value); 

//Грамматический костыль
Including -> NormEnt interp (Including.value) "у" "взрослого" "человека" "срослись" "и" Word<kwtype="включение"> NormEnt interp (Including.list);
Including -> list interp (Including.value) Comma "соединяясь" Word<kwtype="вместе"> SuperEnt ;// Comma Word<kwtype="включение"> NormEnt interp (Including.list);
Including -> SuperEnt interp (Including.list) Word<kwtype="включение"> list interp (Including.value) ("—") SuperEnt ";" interp (+Including.value) NormEnt interp (+Including.value) ";" interp (+Including.value) SuperEnt interp (+Including.value);

//including -> "У" NormEnt interp(Including.list) Word<kwtype="включение">
//Including -> SuperEnt interp (Including.list) Word<kwtype="включение"> ("на") ;   
//Including -> list interp (Including.value) Word<kwtype="включение">

//Невзятые факты
//Including -> Word<kwtype="включение"> interp (Including.value); 


//3 связь. Связь соединения, стыковки.
//super -> NormEnt "вместе" "с" (Word<gram="SPRO">) NormEnt;

//Connection -> ("С") NormEnt<gram="твор"> interp(Connection.first) NormEnt<gram="им"> interp(Connection.second) Word<kwtype="включение"> ("при") ("помощи") Word<gram="род"> interp (Connection.with);
//Connection -> NormEnt interp (Connection.first) Word<kwtype="присоединение"> ("c") NormEnt interp (Connection.second ::not_norm);

Connection -> NormEnt interp (Connection.first ::not_norm) (info) Word<kwtype="присоединение"> (listadv) (Word<kwtype="вместе">) NormEnt interp (Connection.second);
Connection -> NormEnt interp (Connection.first ::not_norm) (info) Word<kwtype="присоединение"> (listadv) (Word<kwtype="вместе">) SuperEnt interp (Connection.second);
Connection -> SuperEnt interp (Connection.first ::not_norm) (info) Word<kwtype="присоединение"> (listadv) (Word<kwtype="вместе">) SuperEnt interp (Connection.second);
Connection -> SuperEnt interp (Connection.first ::not_norm) (info)  Word<kwtype="присоединение"> (listadv) (Word<kwtype="вместе">) NormEnt interp (Connection.second);

Connection -> Word<kwtype="вместе"> NormEnt interp (Connection.first) NormEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> Word<kwtype="вместе"> SuperEnt interp (Connection.first) NormEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> Word<kwtype="вместе"> NormEnt interp (Connection.first) SuperEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> Word<kwtype="вместе"> SuperEnt interp (Connection.first) SuperEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);

Connection -> Word<kwtype="вместе"> NormEnt interp (Connection.first) (Part) Word<kwtype="присоединение"> NormEnt interp (Connection.second);
Connection -> Word<kwtype="вместе"> SuperEnt interp (Connection.first) (Part) Word<kwtype="присоединение"> NormEnt interp (Connection.second);
Connection -> Word<kwtype="вместе"> NormEnt interp (Connection.first) (Part) Word<kwtype="присоединение"> SuperEnt interp (Connection.second);
Connection -> Word<kwtype="вместе"> SuperEnt interp (Connection.first) (Part) Word<kwtype="присоединение"> SuperEnt interp (Connection.second);

Connection -> NormEnt interp (Connection.first) Word<kwtype="вместе"> NormEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> SuperEnt interp (Connection.first) Word<kwtype="вместе"> NormEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> NormEnt interp (Connection.first) Word<kwtype="вместе"> SuperEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);
Connection -> SuperEnt interp (Connection.first) Word<kwtype="вместе"> SuperEnt interp (Connection.second) Word<kwtype="присоединение"> ("при") SuperEnt interp (Connection.with);

//Connection -> NormEnt interp (Connection.first ::not_norm) Word<kwtype="присоединение"> AnyWord interp (Connection.second) AnyWord interp (+Connection.second);
//Connection -> SuperEnt interp (Connection.first ::not_norm) Word<kwtype="присоединение"> AnyWord interp (Connection.second) AnyWord interp (+Connection.second);

//Connection -> SuperEnt interp (Connection.first) Word<kwtype="присоединение"> Word<kwtype="между"> interp (Connection.with) SuperEnt interp (+Connection.with);
//Connection -> SuperEnt interp (Connection.first) Word<kwtype="присоединение"> Word<kwtype="между"> interp (Connection.with) NormEnt interp (+Connection.with);

friends -> "друг" "с" NormEnt;
Connection -> NormEnt interp(Connection.first :: not_norm) Word<kwtype="присоединение"> friends interp (Connection.second ::not_norm) "при" SuperEnt interp (Connection.with); 
Connection -> Word<kwtype="вместимость"> NormEnt interp(Connection.first :: not_norm) "из" NormEnt interp (Connection.from) Word<kwtype="присоединение"> list interp (Connection.second);
Connection -> SuperEnt interp(Connection.first) (info) Word<kwtype="присоединение"> "на" SuperEnt interp (Connection.second);
Connection -> NormEnt interp(Connection.first) (info) Word<kwtype="присоединение"> "на" NormEnt interp (Connection.second);

Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> Word<kwtype="вместе"> SuperEnt interp (Connection.second);
Connection -> NormEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> Word<kwtype="вместе"> SuperEnt interp (Connection.second);
Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> Word<kwtype="вместе"> list interp (Connection.second);
Connection -> NormEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который">(listadv) Word<kwtype="присоединение"> Word<kwtype="вместе"> list interp (Connection.second);

Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> SuperEnt interp (Connection.second);
Connection -> NormEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> SuperEnt interp (Connection.second);
Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> list interp (Connection.second);
Connection -> NormEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> (listadv) list interp (Connection.second);

Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> ("по") (NormEnt) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") SuperEnt interp (Connection.with);
Connection -> SuperEnt interp(Connection.first) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> ("по") (NormEnt) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") list interp (Connection.with);
Connection -> NormEnt interp(Connection.first ::not_norm) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> ("по") (NormEnt) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") SuperEnt interp (Connection.with);
Connection -> NormEnt interp(Connection.first ::not_norm) (info) Comma ("к") Word<kwtype="который"> (listadv) Word<kwtype="присоединение"> ("по") (NormEnt) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") list interp (Connection.with);

Connection -> SuperEnt interp(Connection.first) (info) (Part) (listadv) Word<kwtype="присоединение"> (listadv) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") SuperEnt interp (Connection.with);
Connection -> NormEnt interp(Connection.first) (info) (Part) (listadv) Word<kwtype="присоединение"> (listadv) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) ("при") SuperEnt interp (Connection.with);
Connection -> NormEnt interp(Connection.first) (info) (Part) (listadv) Word<kwtype="присоединение"> (listadv) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second);
Connection -> NormEnt interp(Connection.first ::not_norm) (Part) (info) (listadv) Word<kwtype="присоединение"> (listadv) Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second) "и" interp(+Connection.second) Word<kwtype="вместе"> interp(+Connection.second) SuperEnt interp(+Connection.second ::not_norm);

Connection -> SuperEnt interp(Connection.first) (info) (listadv) Word<kwtype="присоединение"> Word<kwtype="между"> interp(Connection.second) Word<gram="SPRO"> interp(+Connection.second);

Connection -> NormEnt interp(Connection.first ::not_norm) (info) Comma Word<kwtype="вместе"> Word<kwtype="который"> Word<kwtype="присоединение"> SuperEnt interp (Connection.second);
Connection -> NormEnt interp(Connection.first ::not_norm) (info) Comma Word<kwtype="вместе"> Word<kwtype="который"> Word<kwtype="присоединение"> NormEnt interp (Connection.second);
Connection -> SuperEnt interp(Connection.first ::not_norm) (info) Comma Word<kwtype="вместе"> Word<kwtype="который"> Word<kwtype="присоединение"> SuperEnt interp (Connection.second);
Connection -> SuperEnt interp(Connection.first ::not_norm) (info) Comma Word<kwtype="вместе"> Word<kwtype="который"> Word<kwtype="присоединение"> NormEnt interp (Connection.second);
 
Connection -> ("При") SuperEnt interp (Connection.with) NormEnt interp(Connection.first)(listadv) Word<kwtype="присоединение"> friends interp (Connection.second ::not_norm); 

Connection -> list interp(Connection.first) Comma Word<kwtype="который"> Word<kwtype="присоединение"> friends interp (Connection.second ::not_norm) Word<kwtype="вместимость"> SuperEnt interp (Connection.from); 

Connection -> SuperEnt interp(Connection.first ::not_norm) Word<kwtype="присоединение"> "при" SuperEnt interp (Connection.with);

Connection -> Word<kwtype="присоединение"> SuperEnt interp(Connection.first) Word<kwtype="вместе"> list interp (Connection.second);
Connection -> Word<kwtype="присоединение"> list interp (Connection.first);
Connection -> NormEnt interp (Connection.first) Comma Word<kwtype="присоединение"> ("по") (NormEnt) Word<kwtype="вместе"> SuperEnt interp (Connection.second);

//Остальные невзятые факты
//Connection -> Word<kwtype="присоединение"> interp (Connection.from); 


//Connection -> NormEnt interp(Connection.first) Word<kwtype="присоединение"> "при" SuperEnt interp (Connection.with);

//Связь равенства. Выглядит вполне неплохо, но нужно еще добавить разных случаев.

//sum -> NormEnt<gram="твор"> NormEnt<gram="род"> ('и') (",") (NormEnt<gram="род">)  ('и') (",") (NormEnt<gram="род">); 
//eq -> odnor interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2 ::not_norm); 
//eq -> sum interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2 ::not_norm); 
//eq -> NormEnt interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> doplist interp (Equality.Name2:: not_norm);

eq -> list interp (Equality.Name1 ::not_norm) Word<kwtype="между"> list interp (Equality.option ::not_norm) (info) Word<kwtype="равенство"> list interp (Equality.Name2:: not_norm);
eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство"> list interp (Equality.Name2:: not_norm) Word<kwtype="между"> list interp (Equality.option ::not_norm);
//eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство",gram="V"> list interp (Equality.Name2:: not_norm) Comma PartExtend interp (Equality.option ::not_norm) ;
eq -> list interp (Equality.Name1 ::not_norm) (info) Word<kwtype="равенство",gram="V"> ("собой") list interp (Equality.Name2:: not_norm);
eq -> list interp(Equality.Name1 :: not_norm) (info) Word<kwtype="равенство"> (Word<gram="SPRO">) SuperEnt interp (Equality.Name2:: not_norm); 
eq -> NormEnt interp(Equality.Name1) Word<kwtype="равенство"> ("также") NormEnt<gram="твор"> interp (Equality.Name2); 

eq -> NormEnt interp(Equality.Name1 :: not_norm) "вместе" "с" Word<gram="SPRO"> interp (Equality.option ::not_norm) NormEnt interp(+Equality.option :: not_norm) Word<kwtype="равенство"> SuperEnt interp(Equality.Name2:: not_norm);
eq -> NormEnt interp(Equality.Name1 :: not_norm) Comma Word<kwtype="равенство"> SuperEnt interp (Equality.Name2 ::not_norm);

eq -> NormEnt interp(Equality.Name1 ::not_norm) Part (info) Word<kwtype="равенство"> diaplist interp (Equality.Name2::not_norm);
//Работа с тире (доделать)  
//eq -> eqe interp (Equality.Name1 ::not_norm);
//tire -> NormEnt interp (Equality.Name1 ::not_norm) (info) '—' ("это") NormEnt interp (Equality.Name2:: not_norm) Comma PartExtend interp (Equality.option ::not_norm);
tire -> NormEnt interp (Equality.Name1 ::not_norm) (info) "—" ("это") NormEnt interp (Equality.Name2:: not_norm);
tire -> NormEnt interp (Equality.Name1 ::not_norm) (info) "—" ("это") SuperEnt interp (Equality.Name2:: not_norm);
tire -> NormEnt interp (Equality.Name1 ::not_norm) (info) "—" ("это") eq interp (Equality.Name2:: not_norm); 
tire -> SuperEnt interp (Equality.Name1 :: not_norm) (info) "—" ("это") NormEnt interp (Equality.Name2:: not_norm);
tire -> SuperEnt interp (Equality.Name1 :: not_norm) (info) "—" ("это") SuperEnt interp (Equality.Name2:: not_norm);
//Диапазон
diap -> "от" chislit "до" chislit;
diap -> chislit "—" chislit;


//eq ->  Word<kwtype="равенство"> interp (Equality.Name1);
// Связь образования
//obrazovanie -> NormEnt interp (Formation.first) Comma 




//Связь отличия (Отличие винта от блока состоит в том, что борозда расположена не перпендикулярно оси сустава, а по спирали.)
//otlich -> NormEnt interp (Difference.first) ('в') ('отличие') ('от');// NormEnt interp (Difference.second); //Word<kwtype="равенство">; //"в" "том" Comma "что"  
//otlich -> "Отличие" NormEnt //Word<kwset=["сущ","допслова"], GU=["S","род"]> 
//interp (Difference.first) "от" NormEnt interp (Difference.second);// Word<kwtype="равенство"> 



//Примеры
//primer -> NormEnt<gram="твор"> NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
primer -> (NormEnt) NormEnt<gram="род"> Word<kwtype="включение",gram="V">;
prim -> primer interp (Example.state) list interp (Example.state);
//Word<kwtype="включение",gram="V"> list interp(Example.value);


//Перевод с латинского  (Работает)
lat -> LBracket AnyWord<~lat>* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
//lat -> LBracket AnyWord* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
Grec -> lat AnyWord<wfm=~"[)]{1}">* interp(+Translate.grec) RBracket;
//Translate -> Ent interp(Translate.ru) Grec;
Translate -> list interp(Translate.ru) Grec;
Translate -> adjent interp (Translate.ru) Grec;
//Translate -> list interp(Equality.Name1) Grec;

//Вывод.
//Final -> NormEnt interp(Entity.Name ::not_norm);
//Final -> SuperEnt interp (Example.state :: not_norm);
//Final -> list interp (Translate.grec :: not_norm);
//Final -> listrod interp (Difference.first :: not_norm);
//Final -> ExtendAdj interp(Example.state :: not_norm);
//Final -> listrod interp(Example.state :: not_norm);
//Final -> Part interp (Example.state);
//Final -> Word<gram="V">;

//Final -> sum;
//Final -> list;
//Final -> info interp (Example.state :: not_norm);

Final -> Including;
Final -> eq;
Final -> Connection;
Final -> tire;

//Final -> PartExtend;
//Final -> Oborot;

//Final -> Translate;
//Final -> Sinonim;


All -> Final;