<?php

// Set the content type to be XML, so that the browser will   recognise it as XML.
header( "content-type: application/xml; charset=ISO-8859-15" );

// "Create" the document.
$xml = new DOMDocument( "1.0", "ISO-8859-15" );

// Create some elements.
$xml_album = $xml->createElement( "Album" );
$xml_track = $xml->createElement( "Track", "The ninth symphony" );

// Set the attributes.
$xml_track->setAttribute( "length", "0:01:15" );
$xml_track->setAttribute( "bitrate", "64kb/s" );
$xml_track->setAttribute( "channels", "2" );

// Create another element, just to show you can add any (realistic to computer) number of sublevels.
$xml_note = $xml->createElement( "Note", "The last symphony composed by Ludwig van Beethoven." );

// Append the whole bunch.
$xml_track->appendChild( $xml_note );
$xml_album->appendChild( $xml_track );

// Repeat the above with some different values..
$xml_track = $xml->createElement( "Track", "Highway Blues" );

$xml_track->setAttribute( "length", "0:01:33" );
$xml_track->setAttribute( "bitrate", "64kb/s" );
$xml_track->setAttribute( "channels", "2" );
$xml_album->appendChild( $xml_track );

$xml->appendChild( $xml_album );

// Parse the XML.
print $xml->saveXML();

?>