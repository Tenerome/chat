.pragma library
//define const
const SOCKET_LOG_UP = 0
const SOCKET_LOG_IN = 1
const SOCKET_ADD_CONTACT = 2
const SOCKET_ANSWER_ADD = 3
const SOCKET_SELECT_WHEN_START = 4
const SOCKET_MESSAGE = 5
const SOCKET_EDIT_CONTACT = 6
const SOCKET_GET_PROFILE = 7
//CLIENT signale
const CLIENT_FALSE = 0
const CLIENT_TRUE = 1
const CLIENT_ACCOUNT_REGISTED = 2
const CLIENT_ACCOUNT_NOT_REGISTED = 3
const CLIENT_WRONG_PASSWORD = 4
const CLIENT_ACCOUNT_ONLINE = 5
const CLIENT_BUFFER_ADD_CONTACT = 6
const CLIENT_BUFFER_SEND_MESSAGE = 7
const CLIENT_ADD_CONTACT_REQUEST = 8
const CLIENT_AGREE_ADD_CONTACT = 9
const CLIENT_REJECT_ADD_CONTACT = 10
const CLIENT_ANSWER_YES = 11
const CLIENT_ANSWER_NO = 12
const CLIENT_CONTACT_LIST = 13
const CLIENT_TEXT_MESSAGE = 14
const CLIENT_EDIT_NICKNAME = 15
const CLIENT_DELETE_CONTACT = 16
const CLIENT_GROUP_MESSAGE = 17
//global variable
var account = ""
var uid = ""
var name = ""
//transmit variable
var add_page_listmodel
var contact_json
var chatroom_listmodel
var load_model
