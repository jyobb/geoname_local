<?php

/**
 * @file
 * Drush hooks.
 */

/**
 * Implements hook_drush_command().
 */
function geoname_local_drush_command() {
  $items = array();

  $items['geoname_local_load'] = array(
    'aliases' => array('geol'),
    'description' => 'Load Geonames data into tables.',
    'drupal dependencies' => array('geoname_local'),
    'examples' => array(
      'drush -v --user=admin --uri=http://islandorasev_dev.ca islandora --data="geonames" --filepath="data/CA.txt"',
    ),
    'options' => array(
      'data' => array(
        'description' => 'geonames or admin1codes',
        'required' => TRUE,
      ),
      'filepath' => array(
        'description' => 'path from module root.',
        'required' => TRUE,
      ),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_LOGIN,
  );

return $items;

}


/**
 * Implements drush_COMMAND_validate() for geoname_local
 */
function drush_geoname_local_validate() {
  
  //Test file exists
  $base = drupal_get_path('module', 'geoname_local');
  $filepath = drush_get_option('filepath');
  if (!file_exists($base . '/' .$filepath)) {
    drush_set_error('INVALID PATH');
  }

  //Test valid data
  $datatypes = array('geonames', 'admin1codes');
  $data = drush_get_option('data');
  if (!in_array($data, $datatypes)) {
    drush_set_error('INVALID DATATYPE');
  }
}



function drush_geoname_local_load(){

  $filepath = drush_get_option('filepath');
  $data = drush_get_option('data');

  $base = drupal_get_path('module', 'geoname_local');

  $csv_file = DRUPAL_ROOT . '/' . $base . '/' . $filepath;

if(strcmp($data, 'admin1codes') == 0 ){

  if (($handle = fopen($csv_file, "r")) !== FALSE) {
    fgetcsv($handle);
    while (($data = fgetcsv($handle, 0, "\t")) !== FALSE) {
    $path_id = db_insert('geoname_local_admincodes')
      ->fields(array(
      'admin_code' => $data[0],
      'name' => $data[1],
      'asciiname' => $data[2],
      'integer_id' => $data[3],
    ))
    ->execute();
    //echo $data[0] . " : " . $data[1]. " : " . $data[2] . " : " . $data[3] ."\n";
    }
    fclose($handle);
  }
} elseif(strcmp($data, 'geonames') == 0 ){


  if (($handle = fopen($csv_file, "r")) !== FALSE) {
    fgetcsv($handle);
    while (($data = fgetcsv($handle, 0, "\t")) !== FALSE) {
    $path_id = db_insert('geoname_local_geonames')
      ->fields(array(
      'integer_id' => $data[0],
      'name' => $data[1],
      'asciiname' => $data[2],
      'latitude' => $data[4],
      'longitude' => $data[5],
      'country_code' => $data[8],
      'admin1_code' => $data[10],
      'admin2_code' => $data[11],
      'admin_code' => $data[8] .".".$data[10],
    ))
    ->execute();
    }
    fclose($handle);
  }
}else{

    drush_set_error('Error with type match');

}







}