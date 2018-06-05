/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include "iscool/files/default_file_system_delegates.h"
#include "iscool/files/setup.h"
#include "iscool/style/loader.h"
#include "iscool/style/setup.h"
#include "iscool/style/json/from_declaration.h"

#include <json/writer.h>

#include <boost/optional.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string/predicate.hpp>

#include <fstream>
#include <iostream>

struct options
{
    std::string root_directory;
    std::vector< std::string > files;
    std::vector< std::string > search_path;
};

options build_options( const boost::program_options::variables_map& arguments )
{
    options result;
    result.root_directory = arguments[ "root" ].as< std::string >();
    result.files = arguments[ "input-file" ].as< std::vector< std::string > >();
    result.search_path =
        arguments[ "search-path" ].as< std::vector< std::string > >();

    return result;
}

void show_help
( std::ostream& out, const std::string& program_name,
  const boost::program_options::options_description& options )
{
    out << "Usage:\n"
        << program_name
        << " [ --help ] --root=directory --search-path=directory"
        << " style-file…\n\n"
        << options << '\n';
}

boost::optional< options > parse_arguments( int argc, char** argv )
{
    boost::program_options::options_description options( "Options" );
    options.add_options()
        ( "help", "Display this message and exit." )
        ( "root",
          boost::program_options::value< std::string >()->value_name
          ( "directory" ),
          "Set the root directory where the files are searched." )
        ( "input-file",
          boost::program_options::value< std::vector< std::string > >()
          ->value_name( "style-file" ),
          "The path of a style file to merge." )
        ( "search-path",
          boost::program_options::value< std::vector< std::string > >()
          ->value_name( "directory" ),
          "A subdirectory of root-path where to search the style files." );

    boost::program_options::positional_options_description positional_options;
    positional_options.add( "input-file", -1 );

    boost::program_options::variables_map variables;
    boost::program_options::store
        ( boost::program_options::command_line_parser( argc, argv )
          .options( options )
          .positional( positional_options ).run(),
          variables );
    
    boost::program_options::notify( variables );
    
    if ( variables.count( "help" ) != 0 )
    {
        show_help( std::cout, argv[ 0 ], options );
        return boost::none;
    }

    if ( variables.count( "root" ) == 0 )
    {
        show_help( std::cerr, argv[ 0 ], options );
        std::cerr << "Error: the root directory is not set.\n";
        return boost::none;
    }
    
    if ( variables.count( "search-path" ) == 0 )
    {
        show_help( std::cerr, argv[ 0 ], options );
        std::cerr << "Error: the search path is not set.\n";
        return boost::none;
    }
    
    return build_options( variables );
}

std::string cleanup_file_name( std::string file )
{
    std::string extension( ".json" );

    if ( boost::algorithm::ends_with( file, extension ) )
        file.resize( file.size() - extension.size() );

    return file;
}

bool merge_style( const std::string& file )
{
    const iscool::style::declaration style
        ( iscool::style::loader::load( cleanup_file_name( file ) ) );

    Json::Value jsonContent( Json::objectValue );
    jsonContent[ "style" ] = iscool::style::json::from_declaration( style );

    Json::StreamWriterBuilder builder;
    builder[ "commentStyle" ] = "None";
    builder[ "indentation" ] = "";
    builder[ "enableYAMLCompatibility" ] = false;
    builder[ "dropNullPlaceholders" ] = false;
    builder[ "useSpecialFloats" ] = false;
    
    const std::unique_ptr< Json::StreamWriter > writer
        ( builder.newStreamWriter() );

    return writer->write( jsonContent, &std::cout ) == 0;
}

int main( int argc, char** argv )
{
    const boost::optional< options > options( parse_arguments( argc, argv ) );

    if ( !options )
        return 0;

    const iscool::files::default_file_system_delegates file_delegates
        ( options->root_directory, "/tmp/" );
    iscool::files::initialize( file_delegates );

    bool error( false );
    
    if ( options->files.empty() )
    {
        std::cerr << "No file given.\n";
        error = true;
    }
    else
    {
        iscool::style::initialize( options->search_path );
        
        for ( const std::string& file : options->files )
            if ( !merge_style( file ) )
            {
                std::cerr << "Failed to process file '" << file << "'.\n";
                error = true;
            }

        iscool::style::finalize();
    }

    iscool::files::finalize();
    
    return error;
}
