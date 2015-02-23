<?php
/**
 * @file
 * menu_link_options.api.inc
 */

/**
 * Allows modules to define options editable via the menu link edit form.
 *
 * @return array
 *   Returns an associative array, defining option groups and options (types).
 */
function hook_menu_link_options_info() {
  return array(
    'group' => array(
      // A unique human readable label for this group of option types.
      'label' => t('My options group'),
      // An associative array of option information, keyed by the option's
      // machine name.
      'types' => array(
        'machine_name' => array(
          // The title and description are translated strings to be used as
          // labels and descriptive text within the menu link edit forms.
          'title' => t('Option A'),
          'description' => t('This is a basic description of Option A.'),
          // The `element callback` is a callable function which is used for
          // building and returning the renderable form element array. If no
          // element callback is specified, the default callback is:
          // `MODULE_menu_link_options_form_element`.
          'element callback' => 'MODULE_menu_link_options_form_element',
          // The `validate callback` is a callable function which is used for
          // validating the values submitted via the menu edit form for this
          // specific option. The default callback is:
          // `MODULE_menu_link_options_form_element`.
          'validate callback' => 'MODULE_menu_link_options_form_element_validate',
          // The `submit callback` is a callable function which is used for
          // performing any operations on the value that has been validated and
          // is now ready for saving to the menu link's `options` key. The
          // default callback is: `MODULE_menu_link_options_form_element_submit`.
          'submit callback' => 'MODULE_menu_link_options_form_element_submit'
        ),
      ),
      // An array of menus in which this option group and its types apply to.
      // If no menus are specified, the options and their elements will be
      // rendered in the menu link edit form for all menus.
      'menus' => array('main-menu'),
    ),
  );
}

/**
 * Allows other modules to alter the option information.
 *
 * @param array $options
 *   An associative array of option group and option structure for altering.
 */
function hook_menu_link_options_info_alter(&$options) {
  if (isset($options['group']) && isset($options['group']['types']['machine_name'])) {
    $options['group']['types']['machine_name']['element callback'] = 'MODULE_custom_element_callback';
  }
}

/**
 * Form element callback for building and returning the form element array.
 *
 * @param array $type
 *   The option type to build the element for.
 * @param array $element
 *   The base element properties.
 * @param mixed $value
 *   The option's current value.
 * @param array $form
 *   The form structure of the menu link edit form.
 * @param array $form_state
 *   The current form state for the menu link edit form.
 *
 * @return array
 *   Returns the complete renderable form $element.
 */
function hook_menu_link_options_form_element($type, $element, $value, &$form, &$form_state) {
  $element += array(
    '#type' => 'textfield',
    '#default_value' => $value,
  );
  return $value;
}

/**
 * Validation callback handler for an individual option.
 *
 * @param array $type
 *   The option type to build the element for.
 * @param array $element
 *   The base element properties.
 * @param mixed $value
 *   The option's current value.
 * @param array $form
 *   The form structure of the menu link edit form.
 * @param array $form_state
 *   The current form state for the menu link edit form.
 */
function hook_menu_link_options_form_element_validate($type, $element, $value, $form, &$form_state) {
  // Perform validation operations on the $value for this option.
}

/**
 * Submit callback handler for an individual option.
 *
 * @param array $type
 *   The option type to build the element for.
 * @param array $element
 *   The base element properties.
 * @param mixed $value
 *   The option's current value.
 * @param array $form
 *   The form structure of the menu link edit form.
 * @param array $form_state
 *   The current form state for the menu link edit form.
 *
 * @return mixed
 *   Returns the value that should be used for storing in the database.
 */
function hook_menu_link_options_form_element_submit($type, $element, $value, $form, &$form_state) {
  switch ($type['name']) {
    case 'machine_name':
      $value = 'Altered value';
      break;
  }
  return $value;
}
