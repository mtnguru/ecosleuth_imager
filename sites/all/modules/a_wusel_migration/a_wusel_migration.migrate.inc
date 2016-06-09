<?php
    /* all live-data in:
    sites/all/modules/a_wusel_migration/data_sources/
    */
    /* based on: drupal.org/node/1269066#comment-4988994 */
    /* and:      drupal.org/node/1190958#comment-4616032 */
abstract class Wusel_Basic_Migration extends Migration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    parent::__construct(MigrateGroup::getInstance('WuselMigrate'));
  }
}

class Wusel_Step1_UserMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Import an CSV-file (only "Account"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1));
    $this->destination = new MigrateDestinationUser();
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationUser::getKeySchema()
    );

    // Mapped fields
    $this->addSimpleMappings(array('name'));
    $this->addFieldMapping('mail', 'mail')
      ->defaultValue('')
      ->description(t('Email address'));
    $this->addFieldMapping('init')
      ->defaultValue('')
      ->description(t('Email address used for initial account creation'));
    $this->addFieldMapping('pass', 'password')
      ->defaultValue('asdf')
      ->description(t("User's password (plain text)"));
    $this->addFieldMapping('is_new')
      ->defaultValue(TRUE)
      ->description(t('Build the new user (0|1)'));
    $this->addFieldMapping('roles')
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
    $this->addFieldMapping('status')
      ->defaultValue(1)
      ->description(t('Whether the user is active(1) or blocked(0)'));
    $this->addFieldMapping('timezone')
      ->defaultValue(t('Europe/London')) // 'America/Los_Angeles', 'Europe/Berlin', 'UTC', ... from drupal.org/node/714214
      ->description(t("User's time zone"));
    $this->addFieldMapping('language')
      ->defaultValue(t('en')) // e.g.: 'en', 'fr', 'de', ...
      ->description(t("User's default language"));
    $this->addFieldMapping('picture')
      ->defaultValue(0) 
      ->description(t('Avatar of the user'));
 
    // Other handlers
    $this->addFieldMapping('path')
      ->defaultValue(NULL)
      ->description(t('Path alias'));
    if (module_exists('pathauto')) {
      $this->addFieldMapping('pathauto')
        ->defaultValue(1)
        ->description(t('Perform aliasing (set to 0 to prevent alias generation during migration)'));
    }
  }
}

class Wusel_Step2_MemberlistMigration extends Wusel_Basic_Migration {
  public function __construct() {
    parent::__construct();
    global $user;
    $this->description = t('Import an CSV-file with Profile2-fields ("memberlist"-fields)');
    $columns = array(
      // "Source": ('Fieldname', 'Description')
      0 => array('MID', t('Member-ID (must be unique)')),
      1 => array('mail', t('Email (Account)')),
      2 => array('name', t('Name (Account)')),
      3 => array('password', t('Password (Account)')),
      4 => array('complete_name', t('Complete Name (for Memberlist)')),
      5 => array('birthday', t('Birthday (for Memberlist)')),
      6 => array('tel_1', t('Tel.#1 (for Memberlist)'))
    );
    // TIP: delete ", array('header_rows' => 1)" in the next line, if the CSV-file has NO header-line
    $this->source = new MigrateSourceCSV(DRUPAL_ROOT . '/' . drupal_get_path('module', 'a_wusel_migration') . '/data_sources/drupaluser_import.csv', $columns, array('header_rows' => 1));
    // Declare migration 'Wusel_Step1_User' a dependency in migration 'Wusel_Step2_Memberlist' to have them run in the right order, if needed:
    $this->dependencies = array('Wusel_Step1_User');
    $this->destination = new MigrateDestinationProfile2('memberlist');  // 'memberlist' is the "Machine name" of the profile2-"Profile type"
    $this->map = new MigrateSQLMap($this->machineName,
        array('MID' => array( // this field is used to connect user und profile2
                'type' => 'varchar',
                'length' => 6,
                'not null' => TRUE,
                'description' => t('User\'s Member-ID') // description never used
              )
             ),
        MigrateDestinationProfile2::getKeySchema()
    );
    // Connecting the profile2 to the user:
    $this->addFieldMapping('uid', 'MID')
         ->sourceMigration('Wusel_Step1_User')  // If your user migration class was named 'MyUserMigration', the string is 'MyUser'
         ->description(t('The assignment of profile2-items to the respective user'));

    // Mapped fields
    $this->addFieldMapping('field_mnr', 'MID')
      ->defaultValue(0)
      ->description(t('The Member-ID (must be unique)'));
    $this->addFieldMapping('field_mnr:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the Member-ID'));
    $this->addFieldMapping('field_mnr:language')
      ->defaultValue('und')
      ->description(t('The language of the Member-ID<br />("und" = no language)'));
    $this->addFieldMapping('field_username', 'name')
      ->defaultValue('')
      ->description(t('The login name'));
    $this->addFieldMapping('field_username:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the login name'));
    $this->addFieldMapping('field_username:language')
      ->defaultValue(t('en'))
      ->description(t('The language of the login name'));
    $this->addFieldMapping('field_name', 'complete_name')
      ->defaultValue('')
      ->description(t('The complete name (for Memberlist)'));
    $this->addFieldMapping('field_name:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the complete name'));
    $this->addFieldMapping('field_name:language', 'language')
      ->defaultValue(t('en'))
      ->description(t('The language of the complete name'));
    $this->addFieldMapping('field_birthday', 'birthday')
      ->defaultValue('') // empty = unknown
      ->callbacks(array($this, 'fixTimestamp'))
      ->description(t('The birthday (for Memberlist)') . '.<br />' . t('Format') . ': "YYYY-MM-DD" <br />' . t('or') . ' "MM/DD/YYYY" <br />' . t('or') . ' "DD.MM.YYYY"');
    $this->addFieldMapping('field_tel_1', 'tel_1')
      ->defaultValue('')
      ->description(t('The main telephone-number (for Memberlist)'));
    $this->addFieldMapping('field_tel_1:format')
      ->defaultValue('plain_text')
      ->description(t('The Text-Format of the main telephone-number'));
    $this->addFieldMapping('field_tel_1:language', 'language')
      ->defaultValue('und')
      ->description(t('The language of the main telephone-number<br />("und" = no language)'));

    // some internal fields
    $this->addFieldMapping('revision_uid')
      ->defaultValue($user->uid)
      ->description(t('The user ID of the user, who started the migration'));
    $this->addFieldMapping('language')
      ->defaultValue(t('en'))
      ->description(t("The default language of the user (e.g. 'en', 'fr', 'de')"));
    $this->addFieldMapping('path')
      ->defaultValue('')
      ->description(t('Path alias'));

    // Unmapped fields (this fields are in core and not needed as profile2-fields)
    $this->addUnmigratedSources(array('mail', 'password'));
  }

  public function fixTimestamp($date) {
    // enable empty (= unknown) birthday-string:
    if (strlen($date) > 0) {
      $date = substr($date,0,10) . 'T12:00:00'; // we add 'twelve o'clock in the daytime' for automatic compensation of a website time zone difference to UTC
    }
    return $date;
  } 
}
?>
