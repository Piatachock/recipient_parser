function(find_recipient_parser_dependencies)

set(DEPS
  MYBOOST
)

yamail_find_dependencies(RECIPIENT_PARSER "${DEPS}" "")

endfunction()
