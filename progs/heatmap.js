
// This function converts a 0->max_value number to a rgb string for the heatmap
function get_rgb(d,max_value) {
  var ratio = 2 * (d/max_value)
  var r = Math.floor(Math.max(0, 255*(ratio - 1)))
  var b = Math.floor(Math.max(0, 255*(1 - ratio)))
  var g = 255 - b - r
  
  return "rgb(" + r + "," + g + "," + b + ")";
}

function add_heatmap(mydata,x_dim,y_dim,cellsize) {

  var max_value = Math.max.apply(Math, mydata);
  document.write("<svg class=\"heatmap\" width=\"500\" height=\"500\"> </svg>");
  var svg = d3.select(".heatmap")

  var selection = svg.selectAll("rect")
    .data(mydata)

  selection.enter().append("rect")
    .attr("x", function(d,i) { return (i%x_dim)*cellsize; })
    .attr("y", function(d,i) { return (Math.floor(i/x_dim))*cellsize; })
    .attr("width", cellsize)
    .attr("height", cellsize)
    .style("fill", function(d) {return get_rgb(d,max_value);})
}
