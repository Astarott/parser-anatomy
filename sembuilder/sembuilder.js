


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

var is = new java.io.FileInputStream("input.xml");
var doc = org.jsoup.Jsoup.parse(is, "UTF-8", "");

var equality = readEquality(doc.getElementsByTag("equality"));
//print("Equality facts: " + equality.length);
