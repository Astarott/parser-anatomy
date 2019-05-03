#encoding "utf-8"
#GRAMMAR_ROOT All

//Entity -> Adj<gnc-agr[1]>* Noun<gnc-agr[1], gram='S', rt> ;
//SuperEntity -> Entity Word<kwtype="включение"> Entity;
//Fraza ->  Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1]>

//Объявление сущностей
Ent -> Word<kwtype="прил",gnc-agr[1]>* Word<kwtype="сущ", rt, gnc-agr[1]>;
Ent -> Word<kwtype="сущ", gn-agr[1], rt> Word<kwtype="сущ",gn-agr[1],gram="род">+;

//Ent -> 'все' 'вид' Word<kwtype="сущ",gram="вин"> ;

// "костная часть ребра"
Ent -> 'часть' Word<kwtype="сущ",gram="род"> ;
Ent -> Word<kwtype="прил">* 'часть' Word<kwtype="сущ",gram="род"> ;

//Слова-включения (Работает, добавить слова в статью и немного доработать)
mus -> (Ent<gram="вин">) (',') ('и') (Ent<gram="вин">) (',') ('и') (Ent<gram="вин">) (',') ('и') (Ent<gram="вин">) (',') ('и') Ent<gram="вин">;
Including ->  Ent interp(Including.Name1) Word<kwtype="включение"> mus interp(Including.Name2);
Including ->  Ent interp(Including.Name1) 'состоять' 'из' mus interp(Including.Name2);
//Including ->  Ent interp(Including.Name1) Word<kwtype="включение"> mus interp(Including.Name2);

//Работа с тире (доделать)
Including -> Ent interp(Including.Name1) '-' Ent interp(Including.Name2);

//Перевод с латинского  (Работает)
lat -> LBracket AnyWord* Word<lat,wfm=~"[I|V|L|X]{1,10}"> interp(Translate.grec);
Grec -> lat AnyWord* interp(+Translate.grec) RBracket;
//Translate -> Ent interp(Translate.ru) Grec;
Translate -> Word interp(Translate.ru) Grec;

//Уточнения, синонимы и все остальное, что есть в скобках. (Доделать)
info -> LBracket AnyWord<wfm=~"[)]{1}">+ interp(Sin.ent2) RBracket;
Sinonim -> Ent interp(Sin.ent1) info;

//Вывод
//Final -> Ent interp(Entity.Name);
Final -> mus;
Final -> Translate;
Final -> Including;
//Final -> Sinonim;
All -> Final;
