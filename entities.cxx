#encoding "utf-8"
#GRAMMAR_ROOT All

Entity -> Adj<gnc-agr[1]>* Noun<gnc-agr[1], gram='S', rt> ;

SuperEntity -> Entity Word<kwtype="включение"> Entity;



Including -> Entity interp(Including.Name1) Word<kwtype="включение"> Entity interp(Including.Name2);
//Entity -> Noun<gnc-agr[1]> Adj<gnc-agr[1]>+ ;

//Entity -> Noun<rt> Noun<gram='gen'> 'и' Noun<gram='gen'>;
//Entity -> Noun<rt> Noun<gram='gen'>;

//Entity -> Noun;

Final -> Entity interp(Entity.Name);

Final -> Entity interp(Entity.Name);

Final -> Including;

All -> Final;