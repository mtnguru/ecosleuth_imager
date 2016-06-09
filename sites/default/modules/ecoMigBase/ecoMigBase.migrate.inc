<?php
    /* import contacts data from outlook files
     * csv file: /home/eco/migrate/people.csv 
     * based on: drupal.org/node/1269066#comment-4988994 
     * and:      drupal.org/node/1190958#comment-4616032 
     */

function check_phone ($str,&$num,&$ext) {
  $num = "";
  $ext = "";
  if (preg_match('/Ext\.*/i',$str)) {
#   echo("Match Ext $str<br>\n");
    if (preg_match('/(\(\d{3}\) \d{3}-\d{4}) +Ext*\.* +(\d+)/i',$str,$matches)) {
      $num = $matches[1];
      $ext = $matches[2];
    }
  } else {
    if (preg_match('/.*(\(\d{3}\) \d{3}-\d{4}).*/',$str,$matches)) {
      $num = $matches[1];
      $ext = '0';
    }
  }
} 


function explode_phone ($row,$srckey,$numkey,$extkey) {
//echo ("Dude $srckey $numkey $extkey this is fine\n");
  $num = "";
  $ext = "";
  $phone = $row->$srckey;
  if (!empty($phone)) {
    check_phone($row->$srckey,$num,$ext);
    $row->$numkey = $num;
    $row->$extkey = $ext;
  } else {
    $row->$numkey = '';
    $row->$extkey = '';
  }
//echo ("|explode_phone $phone    Num:$num    Ext:$ext|<br>\n");
}

abstract class ecoBasicMigration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('ecoBasicMigration'));
  }
}

class ecoStatusMigration extends ecoBasicMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import Status taxonomy terms from CSV file');
    $this->source = new MigrateSourceCSV('/home/eco/migrate/mediastatus.csv', array(), array('header_rows' => 1));
    $this->destination = new MigrateDestinationTerm('status');
    $this->map = new MigrateSQLMap($this->machineName,
        array('Name' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 80,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields
    $this->addFieldMapping('name', 'Name');
    $this->addFieldMapping('description','Description');
    $this->addFieldMapping('parent_name', 'Parent');
    $this->addFieldMapping('weight', 'Weight');
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    $this->addUnmigratedDestinations(array('path','parent','format'));
    $this->addUnmigratedSources(array('Match'));
  }
}


class ecoWhatMigration extends ecoBasicMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import What taxonomy terms from CSV file');
    $this->source = new MigrateSourceCSV('/home/eco/migrate/what.csv', array(), array('header_rows' => 1));
    $this->destination = new MigrateDestinationTerm('what');
    $this->map = new MigrateSQLMap($this->machineName,
        array('Name' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 80,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields
    $this->addFieldMapping('name', 'Name');
    $this->addFieldMapping('description','Description');
    $this->addFieldMapping('parent_name', 'Parent');
    $this->addFieldMapping('weight', 'Weight');
    $this->addFieldMapping('field_size', 'Size');
    $this->addFieldMapping('field_distance', 'Distance');
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    $this->addUnmigratedDestinations(array('path',
                                           'parent',
                                           'format',
                                           'field_size:language',
                                           'field_distance:language'));
    $this->addUnmigratedSources(array('Match'));
  }
}


class ecoHowMigration extends ecoBasicMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import How taxonomy terms from CSV file');
    $this->source = new MigrateSourceCSV('/home/eco/migrate/how.csv', array(), array('header_rows' => 1));
    $this->destination = new MigrateDestinationTerm('how');
    $this->map = new MigrateSQLMap($this->machineName,
        array('Name' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 80,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields
    $this->addFieldMapping('name', 'Name');
    $this->addFieldMapping('description','Description');
    $this->addFieldMapping('parent_name', 'Parent');
    $this->addFieldMapping('weight', 'Weight');
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    $this->addUnmigratedDestinations(array('path','parent','format'));
    $this->addUnmigratedSources(array('Match'));
  }
}

class ecoUserMigration extends ecoBasicMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import an CSV-file (only "Account"-fields)');
    $this->source = new MigrateSourceCSV('/home/eco/migrate/user.csv', array(),array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName,
        array('Full Name' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 80,
                'not null' => TRUE,
                'description' => t('Users Full Name') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields
    $this->addFieldMapping('name', 'Full Name');
    $this->addFieldMapping('mail', 'E-mail Address');
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));
    $this->addFieldMapping('pass', 'Password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));
    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));
    $this->addFieldMapping('roles','People Type')
      ->separator(',')
      ->defaultValue(DRUPAL_AUTHENTICATED_RID)
      ->description(DRUPAL_AUTHENTICATED_RID . t(' = "authenticated user"'));
    $this->addFieldMapping('theme')
      ->defaultValue('')
      ->description(t("User's default theme"));
    $this->addFieldMapping('signature')
      ->defaultValue('')
      ->description(t("User's signature"));
    $this->addFieldMapping('signature_format')
      ->defaultValue('filtered_html')
      ->description(t('Which filter applies to this signature'));
    $this->addFieldMapping('created')
      ->defaultValue(time())
      ->description(t('UNIX timestamp of user creation date'));
    $this->addFieldMapping('access')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for previous time user accessed the site'));
    $this->addFieldMapping('login')
      ->defaultValue(0)
      ->description(t('UNIX timestamp for user\'s last login'));
    $this->addFieldMapping('status','Active')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));
    $this->addFieldMapping('timezone')
      ->defaultValue(t('America/Denver')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
      ->description(t("User's time zone"));
    $this->addFieldMapping('language')
      ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
      ->description(t("User's default language"));
    $this->addFieldMapping('picture','Picture')
      ->description(t('Avatar of the user'))
      ->defaultValue(1);
 
    // Other handlers
//  $this->addFieldMapping('path')
//    ->defaultValue(NULL)
//    ->description(t('Path alias'));
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
    $this->addUnmigratedDestinations(
       array('role_names',
             'data',
             'path',
//           'field_employee_status',
//           'field_employee_status:source_type',
//           'field_employee_status:create_term',
//           'field_employee_status:ignore_case',
//           'field_status_description',
//           'field_status_description:language',
             ));
    $this->addUnmigratedSources(
       array('Business Fax',
             'Business Phone',
             'Birthday',
             'E-mail Address',
             'Facility Name',
             'First Name',
             'Home City',
             'Home Country/Region',
             'Home Fax',
             'Home Phone',
             'Home Postal Code',
             'Home State',
             'Home Street',
             'Mobile Phone',
             'Notes',
             'Password',
             'Suffix',
             'Title',
             'Job Title',
             'Last Name',
             'Middle Name',
             'Full Name',
             'Children',));
  }
}
  


?>
