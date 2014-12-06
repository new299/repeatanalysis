function add_linegraph(mydata,length) {

  document.write("<svg class=\"linegraph\" width=\"500\" height=\"500\"> </svg>");

  var svg = d3.select(".linegraph")

  var selection = svg.selectAll("line")
    .data(mydata)

  var valueline = d3.svg.line()
      .x(function(d,i) { return i*2; })
      .y(function(d,i) { return d; });

  selection.enter().append("path")
    .attr("class", "line")
    .attr("d", valueline(mydata))
    .style("fill","none")
    .style("stroke","steelblue")
}
