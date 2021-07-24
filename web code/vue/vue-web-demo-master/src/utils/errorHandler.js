/**
 * vue组件接口请求异常处理函数
 * @param {Object} error 错误对象
 * @param {Object} instance
 */
export function errorHandler (error, instance) {
  const data = error.data;

  console.error(error);
  if (data && data.code) {
    if (!data.code || data.code === 404) {
      instance.exception = {
        code: '404',
        msg: window.gettext('当前访问的页面不存在')
      };
    } else if (data.code === 403) {
      instance.exception = {
        code: '403',
        msg: window.gettext('sorry，您没有访问权限!')
      };
    } else if (data.code === 405) {
      instance.exception = {
        code: '405',
        msg: window.gettext('Sorry，您的权限不足!')
      };
    } else if (data.code === 406) {
      instance.exception = {
        code: '405',
        msg: window.gettext('Sorry，您的权限不足!')
      };
    } else if (data.code === 500) {
      instance.exception = {
        code: '500',
        msg: window.gettext('系统出现异常, 请记录下错误场景并与开发人员联系, 谢谢!')
      };
    } else if (data.code === 502) {
      instance.exception = {
        code: '502',
        msg: window.gettext('系统出现异常, 请记录下错误场景并与开发人员联系, 谢谢!')
      };
    }
  } else {
    instance.bkMessageInstance = instance.$bkMessage({
      theme: 'error',
      message: error.message || error.data.msg
    });
  }
}
