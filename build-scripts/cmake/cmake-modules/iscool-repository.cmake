function( iscool_module_directory result module_name subtree )

  set( path ${source_root}/modules/core/${module_name}/${subtree}/iscool )
  
  if( NOT ${module_name} STREQUAL core )
    set( path ${path}/${module_name} )
  endif()

  set( ${result} ${path} PARENT_SCOPE )
endfunction()

function( iscool_module_include_directory result module_name subtree )

  set( ${result}
    ${source_root}/modules/core/${module_name}/${subtree}/include
    PARENT_SCOPE
    )
endfunction()

function( iscool_module_include_argument result module_name )

  iscool_module_include_directory( path ${module_name} module )
  set( ${result} ${path} PARENT_SCOPE )
endfunction()

function( iscool_module_source_root result module_name )

  iscool_module_directory( path ${module_name} module/src )
  set( ${result} ${path} PARENT_SCOPE )
endfunction()

function( iscool_module_android_root result module_name )

  set( path ${source_root}/modules/core/${module_name}/android/java )
  set( ${result} ${path} PARENT_SCOPE )
endfunction()

function( iscool_module_test_include_argument result module_name )

  iscool_module_include_directory( path ${module_name} tests )
  set( ${result} ${path} PARENT_SCOPE )
endfunction()

function( iscool_module_test_source_root result module_name )

  iscool_module_directory( path ${module_name} tests/src )
  set( ${result} ${path} PARENT_SCOPE )
endfunction()
