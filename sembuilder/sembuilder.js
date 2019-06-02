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
	if (a.length == 0)
	{
	    t += line[j].text;
	    continue;
	}
	t += a[0].lex;
    }
    t = t.replaceAll("\n", "");
    res.push({line: t, src: lines[i]});
}
    return res;
}

var entities = [];
function entity(str)
{
    if (str == null || str == undefined || str.trim().isEmpty())
	return;
    for(var i = 0;i < str.length;i++)
	if (str[i] >= '0' && str[i] <= '9')
	    return;
    var items = str.toLowerCase().split(",", -1);
    for(var i = 0;i < items.length;i++)
    {
	if (items[i].trim().isEmpty())
	    continue;
	var items2 = items[i].split(" и ", -1);
	for(var j = 0;j < items2.length;j++)
	    if (!items2[j].trim().isEmpty())
		entities.push(items2[j].trim());
    }
}

function lastWords(str, num)
{
    if (num == 0)
	return "";
    var w = str.split(" ");
    var words = [];
    for(var i = 0;i < w.length;i++)
	if (!w[i].trim().isEmpty())
	    words.push(w[i].trim());
    if (words.length == 0)
	return "";
    var n = words.length > num?num:words.length;
    var fromPos = words.length - n;
    var b = new java.lang.StringBuilder();
    b.append(words[fromPos]);
    for(var i = fromPos + 1;i < words.length;i++)
	b.append(" ").append(words[i]);
    return b.toString();
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



var entities2= [];
var entitiesSet = new java.util.HashSet();
for(var i = 0;i < entities.length;i++)
{
    if (entitiesSet.contains(entities[i]))
	continue;
    entities2.push(entities[i]);
    entitiesSet.add(entities[i]);
}
entities = entities2;
entities2 = null;
entitiesSet = null;
entities.sort();


res = norm(entities);

var processed = new java.util.HashSet();
for(var i = 0;i < res.length;i++)
{
    var line = res[i].line;
    line = lastWords(line, 1);
    if (processed.contains(line))
	continue;
    processed.add(line);
    if (line.startsWith("это ") || line.startsWith("этот "))
	continue;
    if (line.startsWith("а "))
	continue;
    if (line.startsWith("он ") || line.startsWith("она "))
	continue;
    print(line);
    for(var j = 0;j < res.length;j++)
    {
	var e = res[j].line;
	if (e.endsWith(" " + line) && e.length() > line.length)
	{
	    var s = lastWords(e, 2);
	    if (s.startsWith("каждый ") || s.startsWith("этот ") || s.startsWith("это "))
		continue;
	    if (s.startsWith("она ") || s.startsWith("другой") || s.startsWith("свой "))
		continue;
	    var id = line + " : " + s;
	    if (processed.contains(id))
		continue;
	    processed.add(id);
	    print("+" + s);
	}
    }
}
