


function readEquality(nodes)
{
    var res = [];
    for(var i = 0;i < nodes.length;i++)
    {
	var children = nodes[i].childNodes();
	var name1 = "";
	var name2 = "";
	var opt = "";
	for(var j = 0;j < children.size();j++)
	{
	    var ch = children.get(j);
	    	    var name = ch.tagName();
	    var text = ch.attr("val");
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
	res.push({name1: name1, name2: name2, opt: opt});
    }
    return res;
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


function readConnection(nodes)
{
    var res = [];
    for(var i = 0;i < nodes.length;i++)
    {
	var children = nodes[i].childNodes();
	var first = "";
	var second = "";
	var wth = "";
//	var opt = "";
	for(var j = 0;j < children.size();j++)
	{
	    var ch = children.get(j);
	    	    var name = ch.tagName();
	    var text = ch.attr("val");
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
	res.push({first: first, second: second, wth: wth});
    }
    return res;
}

var is = new java.io.FileInputStream("input.xml");
var doc = org.jsoup.Jsoup.parse(is, "UTF-8", "");
var equality = readEquality(doc.getElementsByTag("equality"));
var connection = readConnection(doc.getElementsByTag("connection"));

var including = readFacts(doc.getElementsByTag("including"), function(tags)
{
	var list = "";
	var value = "";
//	var opt = "";
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
    return {in: list, value: value};
});

/*
for(var i = 0;i < equality.length;i++)
    print(equality[i].name1 + "=" + equality[i].name2 + " (" + equality[i].opt + ")");
*/
/*
for(var i = 0;i < connection.length;i++)
    print(connection[i].first + "=" + connection[i].second + " (" + connection[i].wth + ")");
*/

for(var i = 0;i < including.length;i++)
    print(including[i].value + " (в) " + including[i].in );



