namespace NoResultsHelper {
  // Helper to render the /common/no_results partial custamizable content.
  // Example usage:
  // no_results_box action_url: new_project_version_path(this->project),
  //                display_action: authorize_for('messages', 'new')
  //
  // All arguments are optional.
  //  - 'action_url' The url for the link in the content.
  //  - 'display_action' Whether or not the link should be displayed.
  //  - 'custom_title' custom text for the title.
  //  - 'custom_action_text' custom text for the title.
  //
  // Calling this on its on without any arguments creates the box in its simplest
  // form with only the title. Providing an action_url and display_action: true
  // Displays the box with the title and link to the passed in url.
  // The title and action_text are found using the locales key lookup unless
  // custom_title and custom_action_text are provided.
   void no_results_box(action_url:         nil,
                     display_action:     false,
                     custom_title:       nil,
                     custom_action_text: nil)

    title = custom_title || t('.no_results_title_text', cascade: true)
    action_text = custom_action_text || t('.no_results_content_text')

    render partial: '/common/no_results',
           locals: {
             title_text:  title,
             action_text: display_action ? action_text : '',
             action_url:  action_url || ''
           }
  }
}
