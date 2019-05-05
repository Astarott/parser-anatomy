
function runMystem(lines)
{
    var tmpFile = java.io.File.createTempFile("mystem-", ".tmp");
    var w = new java.io.BufferedWriter(new java.io.OutputStreamWriter(new java.io.FileOutputStream(tmpFile)));
    for(var i = 0;i < lines.length;i++)
    {
	w.write(lines[i]);
	w.newLine()
    }
    w.flush();
    w.close();
    var b = new java.lang.ProcessBuilder("mystem", "-c", "--format=json", tmpFile.getAbsolutePath());
    var p = b.start();
    p.getOutputStream().close();
    var r = new java.io.BufferedReader(new java.io.InputStreamReader(p.getInputStream()));
    var res = [];
    var line = r.readLine();
    while(line != null)
    {
	res.push(line);
//	print(line);
	line = r.readLine();
    }
    p.getInputStream().close();
    tmpFile.delete();
    for(var i = 0;i < res.length;i++)
	res[i] = eval(res[i]);
    return res;
}

function norm(lines)
{
    var output = runMystem(lines);
    if (output.length != lines.length)
	print("WARNING: mystem provided  another number of lines");
    var res = [];
for(var i = 0;i < output.length;i++)
{
    var line = output[i];
    var t = "";
    for(var j = 0;j < line.length;j++)
    {
	if (line[j].analysis == undefined)
	{
	    t += line[j].text;
	    continue;
	}
	var a = line[j].analysis;
	t += a[0].lex;
    }
    res.push({line: t, src: lines[i]});
}
    return res;
}

function entity(str)
{
    //print(str);
}

function readFacts(nodes, objFunc)
{
    var res = [];
    for(var i = 0;i < nodes.length;i++)
    {
	var obj = objFunc(nodes[i].childNodes());
	if (obj != null)
	    res.push(obj);
    }
    return res;
}

var is = new java.io.FileInputStream("input.xml");
var doc = org.jsoup.Jsoup.parse(is, "UTF-8", "");

var equality = readFacts(doc.getElementsByTag("equality"), function(tags){
    var name1 = "";
    var name2 = "";
    var opt = "";
    for(var j = 0;j < tags.size();j++)
    {
	var tag = tags.get(j);
	var name = tag.tagName();
	var text = tag.attr("val");
	switch(name.toLowerCase())
	{
	    case "name1":
	    name1 = text;
	    continue;
	    case "name2":
	    name2 = text;
	    continue;
	    case "option":
	    opt = text;
	    continue;
	    default:
	    print("WARNING: Unknown tag in a equality fact: " + name);
	}
    }
    return {name1: name1, name2: name2, opt: opt};
});

var connection = readFacts(doc.getElementsByTag("connection"), function(tags){
    var first = "";
    var second = "";
    var wth = "";
    for(var i = 0;i < tags.size();i++)
    {
	var tag = tags[i];
	var name = tag.tagName();
	var text = tag.attr("val");
	switch(name.toLowerCase())
	{
	    case "first":
	    first = text;
	    continue;
	    case "second":
	    second = text;
	    continue;
	    case "with":
	    wth = text;
	    continue;
	    default:
	    print("WARNING: Unknown tag in a connection fact: " + name);
	}
    }
    return {first: first, second: second, wth: wth};
});

var including = readFacts(doc.getElementsByTag("including"), function(tags) {
    var list = "";
    var value = "";
    for(var j = 0;j < tags.size();j++)
    {
	var tag = tags.get(j);
	var name = tag.tagName();
	var text = tag.attr("val");
	switch(name.toLowerCase())
	{
	    case "list":
	    list = text;
	    continue;
	    case "value":
	    value = text;
	    continue;
	    default:
	    print("WARNING: Unknown tag in a including fact: " + name);
	}
    }
    return {nameIn: list, name: value};
});

/*
for(var i = 0;i < equality.length;i++)
{
    entity(equality[i].name1);
    entity(equality[i].name2);
}
for(var i = 0;i < connection.length;i++)
{
    entity(connection[i].first);
        entity(connection[i].second);
}
for(var i = 0;i < including.length;i++)
{
    entity(including[i].value);
    entity(including[i].nameIn);
}
*/



/*
var res = runMystem([
    "Это пробный текст",
    "Это всё было прошлым летом",
"А это совсем в конце файла"]);

for(var i = 0;i < res.length;i++)
{
    var line = res[i];
    print("LIne: " + i);
    for(var j = 0;j < line.length;j++)
    {
	if (line[j].analysis != undefined)
	{
	    var a = line[j].analysis;
	    //	    print(a.length);
	    for(var k = 0;k < a.length;k++)
		print("L: " + a[k].lex);
	}
//	print("Analysis: " + line[j].analysis);
		print("Text: " + line[j].text);
//		print(line[j][1]);
    }
}
*/

var res = norm(["Это первая строка", "Это вторая строка, которая уже немного длиннее; то-то же!"]);
for(var i = 0;i < res.length;i++)
{
    print(res[i].src);
    print(res[i].line);
}
