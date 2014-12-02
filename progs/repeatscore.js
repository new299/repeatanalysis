
function write_1d_int32_array(ptr,array) {

  for(i=0;i<array.length;i++) {
    Module.setValue(ptr,array[i],'i32');
    ptr += 4;
  }

}

function read_1d_int32_array(ptr,length) {

  var array = [];

  for(i=0;i<length;i++) {
    var value = Module.getValue(ptr+(i*4),'i32');
    array.push(value);
  }

  return array;
}

function get_repeatscore(mystring) {

 // var mystring = "test";
  var strptr = Module._malloc(mystring.length);
  Module.writeAsciiToMemory(mystring, strptr);

  var retarrayptr = Module.ccall('repeat_score', // name of C function
    'number', // return type
    ['number'], // argument types
    [strptr]); // arguments

  // Convert the resulting pointer to a JS array
  return read_1d_int32_array(retarrayptr,10000);
}
