.pragma library
//define const
//10-29
const SOCKET_LOG_UP = 10
const SOCKET_LOG_IN = 11
const SOCKET_ADD_CONTACT = 12
const SOCKET_ANSWER_ADD = 13
const SOCKET_SELECT_WHEN_START = 14
const SOCKET_MESSAGE = 15
const SOCKET_EDIT_CONTACT = 16
const SOCKET_GET_PROFILE = 17
//CLIENT signale
//30->
const CLIENT_FALSE = 30
const CLIENT_TRUE = 31
const CLIENT_ACCOUNT_REGISTED = 32
const CLIENT_ACCOUNT_NOT_REGISTED = 33
const CLIENT_WRONG_PASSWORD = 34
const CLIENT_ACCOUNT_ONLINE = 35
const CLIENT_BUFFER_ADD_CONTACT = 36
const CLIENT_BUFFER_SEND_MESSAGE = 37
const CLIENT_ADD_CONTACT_REQUEST = 38
const CLIENT_AGREE_ADD_CONTACT = 39
const CLIENT_REJECT_ADD_CONTACT = 40
const CLIENT_ANSWER_YES = 41
const CLIENT_ANSWER_NO = 42
const CLIENT_CONTACT_LIST = 43
const CLIENT_TEXT_MESSAGE = 44
const CLIENT_EDIT_NICKNAME = 45
const CLIENT_DELETE_CONTACT = 46
const CLIENT_GROUP_MESSAGE = 47
const CLIENT_IMAGE_MESSAGE = 48
//global variable
var account = ""
var uid = ""
var name = ""
//transmit variable
var add_page_listmodel
var contact_json
var contact_map
var chatroom_model
var load_model
